// Copyright (C) 2022 Thinh Pham.


#include "LobbyPawn.h"
#include "LobbyGameMode.h"
#include "PlayFabGameInstance.h"

ALobbyPawn::ALobbyPawn()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALobbyPawn::BeginPlay()
{
	Super::BeginPlay();

	// send target map to server
	if (IsLocallyControlled())
	{
		if (UPlayFabGameInstance* GInst = GetGameInstance<UPlayFabGameInstance>())
		{
			SubmitTargetMap(GInst->TravelTargetMap);
		}
	}
}

void ALobbyPawn::SubmitTargetMap_Implementation(const FString& TargetMap)
{
	// redirect to game mode to make sure execute only 1 time
	if (ALobbyGameMode* GMode = GetWorld()->GetAuthGameMode<ALobbyGameMode>())
	{
		GMode->SetTargetMap(TargetMap);
	}
}
