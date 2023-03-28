// Copyright (C) 2022 Thinh Pham.


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
}

void UPlayFabMatchComponent::CreateTicket(FString QueueName)
{
	// make request
	CreateTicketRequest.GiveUpAfterSeconds = TicketTimeout;
	CreateTicketRequest.QueueName = QueueName;
	CreateTicketRequest.AuthenticationContext = GetLoginContext();
	CreateTicketRequest.Creator.Attributes = MakeShareable(new FMatchmakingPlayerAttributes);
	TSharedPtr<FJsonObject> J = FJsonObjectConverter::UStructToJsonObject(UserAttributes);
	CreateTicketRequest.Creator.Attributes->DataObject = FJsonKeeper(J);
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
	GetTicketRequest.AuthenticationContext = GetLoginContext();
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
		R.AuthenticationContext = GetLoginContext();
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
		R.AuthenticationContext = GetLoginContext();
		R.MatchId = Result.MatchId;
		R.QueueName = Result.QueueName;
		R.ReturnMemberAttributes = true;
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
	TArray<UPlayFabMatchPlayerEntry*> Players;
	for (FMatchmakingPlayerWithTeamAssignment P : Result.Members)
	{
		if (P.Entity.Id == GetLoginEntityId()) {
			Portal = P.TeamId;
			UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Team %s"), *Portal));
		}
		TSharedPtr<FJsonObject> F = P.Attributes->DataObject.GetJsonValue()->AsObject();
		UPlayFabMatchPlayerEntry* Player = NewObject<UPlayFabMatchPlayerEntry>(this);
		Player->DisplayName = F->GetStringField(TEXT("displayName"));
		Player->AvatarUrl = F->GetStringField(TEXT("avatarUrl"));
		Player->Position = P.TeamId;
		Players.Add(Player);
	}
	// get server address (only available on playfab's mps)
	FString Server;
	if (Result.pfServerDetails.IsValid()) {
		FServerDetails* D = Result.pfServerDetails.Get();
		Server = FString::Printf(TEXT("%s:%d"), *D->IPV4Address, D->Ports[0].Num);
	}
	// broadcast on blueprint side
	OnMatchFound.Broadcast(Server, Portal, Players);
}
