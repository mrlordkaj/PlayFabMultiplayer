// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayFabMatchComponent.h"
#include "PlayFabMultiplayer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "JsonObjectConverter.h"
#include "PlayFabTypes.h"

using namespace PlayFab;
using namespace PlayFab::MultiplayerModels;

void UPlayFabMatchComponent::BeginPlay()
{
	Super::BeginPlay();

	MultiplayerAPI = IPlayFabModuleInterface::Get().GetMultiplayerAPI();

	//TSharedPtr<FJsonObject> J = FJsonObjectConverter::UStructToJsonObject(UserAttributes2);
	//FString Encode;
	//TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Encode);
	//FJsonSerializer::Serialize(J.ToSharedRef(), Writer);
	//UKismetSystemLibrary::PrintString(GetWorld(), Encode);

	//TSharedPtr<FJsonObject> J = MakeShareable(new FJsonObject);
	//J->SetStringField("DisplayName", "DCI Thinh");
	//J->SetStringField("AvatarUrl", "https://google.com.vn");
	//TArray<TSharedPtr<FJsonValue>> Latencies;
	//for (TPair<EAzureRegion, float> R : RegionLatencies) {
	//	TSharedPtr<FJsonObject> O = MakeShareable(new FJsonObject);
	//	O->SetStringField(TEXT("Region"), UEnum::GetDisplayValueAsText(R.Key).ToString());
	//	O->SetNumberField(TEXT("Latency"), R.Value);
	//	Latencies.Add(MakeShareable(new FJsonValueObject(O)));
	//}
	//J->SetArrayField(TEXT("Latencies"), Latencies);
	//FPlayFabUserAttributes A;
	//FJsonObjectConverter::JsonObjectToUStruct(J.ToSharedRef(), &A);
	//UKismetSystemLibrary::PrintString(GetWorld(), UEnum::GetDisplayValueAsText(A.Latencies[0].Region).ToString());
}

void UPlayFabMatchComponent::CreateTicket(FString QueueName)
{
	// make request
	CreateTicketRequest.GiveUpAfterSeconds = TicketTimeout;
	CreateTicketRequest.QueueName = QueueName;
	CreateTicketRequest.AuthenticationContext = GetLoginContextCpp();
	CreateTicketRequest.Creator.Attributes = MakeShareable(new FMatchmakingPlayerAttributes);
	TSharedPtr<FJsonObject> J = FJsonObjectConverter::UStructToJsonObject(UserAttributes);
	CreateTicketRequest.Creator.Attributes->DataObject = FJsonKeeper(J);
	// player entity
	CreateTicketRequest.Creator.Entity.Id = GetLoginEntityId();
	CreateTicketRequest.Creator.Entity.Type = TEXT("title_player_account");
	// TODO: members to match with
	// call api
	UE_LOG(LogPlayFabMultiplayer, Warning, TEXT("%s"), *CreateTicketRequest.toJSONString());
	MultiplayerAPI->CreateMatchmakingTicket(CreateTicketRequest,
		UPlayFabMultiplayerAPI::FCreateMatchmakingTicketDelegate::CreateUObject(this, &UPlayFabMatchComponent::CreateTicketSuccess),
		DefaultErrorCpp);
}

void UPlayFabMatchComponent::CreateTicketSuccess(const PlayFab::MultiplayerModels::FCreateMatchmakingTicketResult& Result)
{
	UE_LOG(LogPlayFabMultiplayer, Display, TEXT("%s"), *Result.toJSONString());
	// create get ticket request
	GetTicketRequest.AuthenticationContext = GetLoginContextCpp();
	GetTicketRequest.QueueName = CreateTicketRequest.QueueName;
	GetTicketRequest.TicketId = Result.TicketId;
	// start refreshing ticket status by the time in settings
	GetWorld()->GetTimerManager().SetTimer(RefreshTicketTimer,
		FTimerDelegate::CreateUObject(this, &UPlayFabMatchComponent::RefreshTicket),
		RefreshTicketPeriod, true, 3);
	// broadcast on blueprint
	OnTicketCreated.Broadcast();
}

void UPlayFabMatchComponent::CancelTicket()
{
	if (!GetTicketRequest.TicketId.IsEmpty())
	{
		// call cancel api
		FCancelMatchmakingTicketRequest R;
		R.AuthenticationContext = GetLoginContextCpp();
		R.QueueName = GetTicketRequest.QueueName;
		R.TicketId = GetTicketRequest.TicketId;
		UE_LOG(LogPlayFabMultiplayer, Warning, TEXT("%s"), *R.toJSONString());
		MultiplayerAPI->CancelMatchmakingTicket(R,
			UPlayFabMultiplayerAPI::FCancelMatchmakingTicketDelegate::CreateUObject(this, &UPlayFabMatchComponent::CancelTicketSuccess),
			DefaultErrorCpp);
	}
}

void UPlayFabMatchComponent::CancelTicketSuccess(const PlayFab::MultiplayerModels::FCancelMatchmakingTicketResult& Result)
{
	// clear ticket info
	GetTicketRequest.TicketId = TEXT("");
	// stop refresh ticket
	GetWorld()->GetTimerManager().ClearTimer(RefreshTicketTimer);
	// broadcast on blueprint
	OnTicketCanceled.Broadcast(TEXT("Requested"));
}

void UPlayFabMatchComponent::RefreshTicket()
{
	UE_LOG(LogPlayFabMultiplayer, Warning, TEXT("%s"), *GetTicketRequest.toJSONString());
	MultiplayerAPI->GetMatchmakingTicket(GetTicketRequest,
		UPlayFabMultiplayerAPI::FGetMatchmakingTicketDelegate::CreateUObject(this, &UPlayFabMatchComponent::GetTicketSuccess),
		DefaultErrorCpp);
}

void UPlayFabMatchComponent::GetTicketSuccess(const PlayFab::MultiplayerModels::FGetMatchmakingTicketResult& Result)
{
	UE_LOG(LogPlayFabMultiplayer, Display, TEXT("%s"), *Result.toJSONString());
	if (Result.Status == TEXT("Matched"))
	{
		// stop refresh ticket
		GetWorld()->GetTimerManager().ClearTimer(RefreshTicketTimer);
		// call get match api
		FGetMatchRequest R;
		R.AuthenticationContext = GetLoginContextCpp();
		R.MatchId = Result.MatchId;
		R.QueueName = Result.QueueName;
		R.ReturnMemberAttributes = false;
		UE_LOG(LogPlayFabMultiplayer, Warning, TEXT("%s"), *R.toJSONString());
		MultiplayerAPI->GetMatch(R,
			UPlayFabMultiplayerAPI::FGetMatchDelegate::CreateUObject(this, &UPlayFabMatchComponent::GetMatchSuccess),
			DefaultErrorCpp);
	}
	else if (Result.Status == TEXT("Canceled"))
	{
		// stop refresh ticket
		GetWorld()->GetTimerManager().ClearTimer(RefreshTicketTimer);
		if (bAutoRenewTicket && Result.CancellationReasonString == TEXT("Timeout"))
		{
			// auto renew
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Renewing Ticket"));
			CreateTicket(CreateTicketRequest.QueueName);
		}
		else {
			// broadcast stop event
			OnTicketCanceled.Broadcast(Result.CancellationReasonString);
		}
	}
}

void UPlayFabMatchComponent::GetMatchSuccess(const PlayFab::MultiplayerModels::FGetMatchResult& Result)
{
	UE_LOG(LogPlayFabMultiplayer, Display, TEXT("%s"), *Result.toJSONString());
	// find my team
	FString Portal;
	for (FMatchmakingPlayerWithTeamAssignment P : Result.Members)
	{
		if (P.Entity.Id == GetLoginEntityId()) {
			Portal = P.TeamId;
			UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Team %s"), *Portal));
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
