// Copyright (C) 2022 Thinh Pham.


#include "PlayFabMatchActor.h"
#include "PlayFabMultiplayer.h"
#include "Kismet/KismetSystemLibrary.h"

using namespace PlayFab;
using namespace PlayFab::MultiplayerModels;

APlayFabMatchActor::APlayFabMatchActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APlayFabMatchActor::BeginPlay()
{
	Super::BeginPlay();

	MultiplayerAPI = IPlayFabModuleInterface::Get().GetMultiplayerAPI();
}

void APlayFabMatchActor::CreateTicket(FString QueueName, FString TargetMapName)
{
	TargetMap = TargetMapName;

	// make request
	CreateTicketRequest.GiveUpAfterSeconds = TicketTimeout;
	CreateTicketRequest.QueueName = QueueName;
	CreateTicketRequest.AuthenticationContext = GetAuthenticationContextCpp();
	// latencies
	TArray<TSharedPtr<FJsonValue>> Latencies;
	for (TPair<EAzureRegion, float> R : RegionLatencies) {
		TSharedPtr<FJsonObject> O = MakeShareable(new FJsonObject);
		O->SetStringField(TEXT("Region"), UEnum::GetDisplayValueAsText(R.Key).ToString());
		O->SetNumberField(TEXT("Latency"), R.Value);
		Latencies.Add(MakeShareable(new FJsonValueObject(O)));
	}
	TSharedPtr<FJsonObject> J = MakeShareable(new FJsonObject);
	J->SetArrayField(TEXT("Latencies"), Latencies);
	CreateTicketRequest.Creator.Attributes = MakeShareable(new FMatchmakingPlayerAttributes());
	CreateTicketRequest.Creator.Attributes->DataObject = FJsonKeeper(J);
	// player entity
	CreateTicketRequest.Creator.Entity.Id = GetEntityId();
	CreateTicketRequest.Creator.Entity.Type = TEXT("title_player_account");
	// TODO: members to match with
	// call api
	UE_LOG(LogPlayFabMultiplayer, Warning, TEXT("%s"), *CreateTicketRequest.toJSONString());
	MultiplayerAPI->CreateMatchmakingTicket(CreateTicketRequest,
		UPlayFabMultiplayerAPI::FCreateMatchmakingTicketDelegate::CreateUObject(this, &APlayFabMatchActor::OnCreateTicketSuccess),
		DefaultErrorDelegate);
}

void APlayFabMatchActor::CancelTicket()
{
	// make request
	FCancelMatchmakingTicketRequest Request;
	Request.AuthenticationContext = GetAuthenticationContextCpp();
	Request.QueueName = GetTicketRequest.QueueName;
	Request.TicketId = GetTicketRequest.TicketId;
	// call api
	UE_LOG(LogPlayFabMultiplayer, Warning, TEXT("%s"), *Request.toJSONString());
	MultiplayerAPI->CancelMatchmakingTicket(Request,
		UPlayFabMultiplayerAPI::FCancelMatchmakingTicketDelegate(),
		DefaultErrorDelegate);
	// stop refresh ticket
	GetWorldTimerManager().ClearTimer(RefreshTicketTimer);
	TicketStatus = TEXT("Canceled");
	// broadcast on blueprint
	OnTicketCancel.Broadcast(TEXT("Requested"));
}

void APlayFabMatchActor::OnCreateTicketSuccess(const FCreateMatchmakingTicketResult& Result)
{
	UE_LOG(LogPlayFabMultiplayer, Display, TEXT("%s"), *Result.toJSONString());
	// create get ticket request
	GetTicketRequest.AuthenticationContext = GetAuthenticationContextCpp();
	GetTicketRequest.QueueName = CreateTicketRequest.QueueName;
	GetTicketRequest.TicketId = Result.TicketId;
	// start refreshing ticket status by the time in settings
	GetWorldTimerManager().SetTimer(RefreshTicketTimer,
		FTimerDelegate::CreateUObject(this, &APlayFabMatchActor::RefreshTicket),
		RefreshTicketPeriod, true, 3);
}

void APlayFabMatchActor::RefreshTicket()
{
	UE_LOG(LogPlayFabMultiplayer, Warning, TEXT("%s"), *GetTicketRequest.toJSONString());
	MultiplayerAPI->GetMatchmakingTicket(GetTicketRequest,
		UPlayFabMultiplayerAPI::FGetMatchmakingTicketDelegate::CreateUObject(this, &APlayFabMatchActor::OnGetTicketSuccess),
		DefaultErrorDelegate);
}

void APlayFabMatchActor::OnGetTicketSuccess(const FGetMatchmakingTicketResult& Result)
{
	UE_LOG(LogPlayFabMultiplayer, Display, TEXT("%s"), *Result.toJSONString());
	TicketStatus = Result.Status;
	if (Result.Status == TEXT("Matched"))
	{
		// stop refresh ticket
		GetWorldTimerManager().ClearTimer(RefreshTicketTimer);
		// create get match request
		FGetMatchRequest Request;
		Request.AuthenticationContext = GetAuthenticationContextCpp();
		Request.MatchId = Result.MatchId;
		Request.QueueName = Result.QueueName;
		// call get match api
		MultiplayerAPI->GetMatch(Request,
			UPlayFabMultiplayerAPI::FGetMatchDelegate::CreateUObject(this, &APlayFabMatchActor::OnGetMatchSuccess),
			DefaultErrorDelegate);
	}
	else if (Result.Status == TEXT("Canceled"))
	{
		// stop refresh ticket
		GetWorldTimerManager().ClearTimer(RefreshTicketTimer);
		if (bAutoRenewTicket && Result.CancellationReasonString == TEXT("Timeout"))
		{
			// auto renew
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Renewing Ticket"));
			CreateTicket(CreateTicketRequest.QueueName, TargetMap);
		}
		else {
			// broadcast stop event
			OnTicketCancel.Broadcast(Result.CancellationReasonString);
		}
	}
}

void APlayFabMatchActor::OnGetMatchSuccess(const FGetMatchResult& Result)
{
	// find my team
	FString Portal;
	for (FMatchmakingPlayerWithTeamAssignment P : Result.Members)
	{
		if (P.Entity.Id == GetEntityId()) {
			UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Team %s"), *Portal));
			Portal = P.TeamId;
			break;
		}
	}
	// get server address (only available on playfab's mps)
	FString Server;
	if (Result.pfServerDetails.IsValid()) {
		FServerDetails* D = Result.pfServerDetails.Get();
		Server = FString::Printf(TEXT("%s:%d"), *D->IPV4Address, D->Ports[0].Num);
	}
	// broadcast on blueprint side
	OnMatchFound.Broadcast(Server, Portal);
}
