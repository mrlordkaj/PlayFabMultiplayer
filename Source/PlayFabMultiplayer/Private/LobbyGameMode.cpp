// Copyright (C) 2022 Thinh Pham.


#include "LobbyGameMode.h"
#include "PlayFabMultiplayer.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ALobbyGameMode::ALobbyGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALobbyGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
	FString& ErrorMessage)
{
	// TODO: accept or reject player
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

APlayerController* ALobbyGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal,
	const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* Controller = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	if (TargetMap.IsEmpty())
	{
		FString ClientTargetMap = UGameplayStatics::ParseOption(Options, "Map");
		if (!ClientTargetMap.IsEmpty())
		{
			TargetMap = ClientTargetMap;
			FTimerHandle Timer;
			FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ALobbyGameMode::TravelTargetMap);
			GetWorldTimerManager().SetTimer(Timer, Delegate, TravelDelay, false);
			UE_LOG(LogPlayFabMultiplayer, Warning, TEXT("Going travel to '%s' after %d seconds"), *TargetMap, TravelDelay);
		}
	}
	return Controller;
}

void ALobbyGameMode::TravelTargetMap() const
{
	if (!GetWorld()->ServerTravel(TargetMap))
	{
		UE_LOG(LogPlayFabMultiplayer, Error, TEXT("Cannot travel to '%s'"), *TargetMap);
	}
}
