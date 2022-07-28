// Copyright (C) 2022 Thinh Pham.


#include "PlayFabGameMode.h"
#include "PlayFabMultiplayer.h"
#include "GSDKUtils.h"

APlayFabGameMode::APlayFabGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APlayFabGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void APlayFabGameMode::Logout(AController* ExitingPlayer)
{
	Super::Logout(ExitingPlayer);

#if UE_SERVER
	if (ShutdownServerWhenNoPlayers) {
		ExitingPlayer->OnDestroyed.AddDynamic(this, &APlayFabGameMode::OnPlayerOut);
	}
#endif
}

void APlayFabGameMode::OnPlayerOut(AActor* PlayerController)
{
	if (GetNumPlayers() < 1)
	{
		FPlatformMisc::RequestExit(false);
		//RequestEngineExit("All players left");
	}
}

void APlayFabGameMode::RegisterPlayFabUser(FString PlayerId)
{
	UE_LOG(PlayFabMultiplayer, Warning, TEXT("PlayFabUser joined: %s"), *PlayerId);
	PlayFabUsers.AddUnique(PlayerId);
	UpdateConnectedPlayers();
}

void APlayFabGameMode::UnregisterPlayFabUser(FString PlayerId)
{
	UE_LOG(PlayFabMultiplayer, Warning, TEXT("PlayFabUser exited: %s"), *PlayerId);
	PlayFabUsers.Remove(PlayerId);
	UpdateConnectedPlayers();
}

int APlayFabGameMode::GetNumPlayFabUsers() const
{
	return PlayFabUsers.Num();
}

void APlayFabGameMode::UpdateConnectedPlayers()
{
	TArray<FConnectedPlayer> Players;
	for (FString PlayerId : PlayFabUsers)
	{
		FConnectedPlayer Player;
		Player.PlayerId = PlayerId;
		Players.Add(Player);
	}
	UE_LOG(PlayFabMultiplayer, Warning, TEXT("Total PlayFabUser(s): %d"), Players.Num());
	UGSDKUtils::UpdateConnectedPlayers(Players);
}
