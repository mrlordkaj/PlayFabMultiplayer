// Copyright (C) 2022 Thinh Pham.


#include "PlayFabMatchActor.h"

using namespace PlayFab::MultiplayerModels;

APlayFabMatchActor::APlayFabMatchActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.5f;
	
	RegionLatencies.Add(FRegionLatency("EastUS"));
}

void APlayFabMatchActor::BeginPlay()
{
	Super::BeginPlay();

	MultiplayerAPI = IPlayFabModuleInterface::Get().GetMultiplayerAPI();
}

void APlayFabMatchActor::CreateTicket(FString MatchQueueName, FString TargetMapName)
{
	TargetMap = TargetMapName;
	MatchQueue = MatchQueueName;

	FJsonObject
	PlayFab::FJsonKeeper Keeper;
	Keeper.readFromValue()

	FCreateMatchmakingTicketRequest Request;
	Request.Creator.Attributes->DataObject = Latencies;

	//MultiplayerAPI->CreateMatchmakingTicket();
}
