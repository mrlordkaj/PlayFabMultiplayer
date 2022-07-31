// Copyright (C) 2022 Thinh Pham.


#include "LobbyGameMode.h"
#include "LobbyPawn.h"
#include "PlayFabMultiplayer.h"
#include "Kismet/KismetSystemLibrary.h"

ALobbyGameMode::ALobbyGameMode()
{
	DefaultPawnClass = ALobbyPawn::StaticClass();
}

void ALobbyGameMode::SetTargetMap(const FString ClientTargetMap)
{
	if (TargetMap.IsEmpty() && !ClientTargetMap.IsEmpty())
	{
		TargetMap = ClientTargetMap;
		FTimerHandle Timer;
		FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ALobbyGameMode::TravelTargetMap);
		GetWorldTimerManager().SetTimer(Timer, Delegate, TravelDelay, false);
		UE_LOG(PlayFabMultiplayer, Warning, TEXT("Going travel to '%s' after %d seconds"), *TargetMap, TravelDelay);
	}
}

void ALobbyGameMode::TravelTargetMap() const
{
	//FString Cmd = "servertravel " + TargetMap;
	//UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), Cmd);
	GetWorld()->ServerTravel(TargetMap);
}
