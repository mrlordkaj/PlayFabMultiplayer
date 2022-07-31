// Copyright (C) 2022 Thinh Pham.


#include "MultiplayerGameMode.h"
#include "PlayFabMultiplayer.h"
#include "GSDKUtils.h"
#include "Kismet/GameplayStatics.h"

AMultiplayerGameMode::AMultiplayerGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMultiplayerGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
	FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	UGameplayStatics::ParseOption(Options, "PlayFabId");
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Options);
}

void AMultiplayerGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AMultiplayerGameMode::Logout(AController* ExitingPlayer)
{
	Super::Logout(ExitingPlayer);

#if UE_SERVER
	if (ShutdownServerWhenNoPlayers) {
		ExitingPlayer->OnDestroyed.AddDynamic(this, &APlayFabGameMode::OnPlayerOut);
	}
#endif
}

void AMultiplayerGameMode::OnPlayerOut(AActor* PlayerController)
{
	if (GetNumPlayers() < 1)
	{
		FPlatformMisc::RequestExit(false);
		//RequestEngineExit("All players left");
	}
}

void AMultiplayerGameMode::RegisterPlayFabUser(FString PlayerId)
{
	UE_LOG(PlayFabMultiplayer, Warning, TEXT("PlayFabUser joined: %s"), *PlayerId);
	PlayFabUsers.AddUnique(PlayerId);
	UpdateConnectedPlayers();
}

void AMultiplayerGameMode::UnregisterPlayFabUser(FString PlayerId)
{
	UE_LOG(PlayFabMultiplayer, Warning, TEXT("PlayFabUser exited: %s"), *PlayerId);
	PlayFabUsers.Remove(PlayerId);
	UpdateConnectedPlayers();
}

int AMultiplayerGameMode::GetNumPlayFabUsers() const
{
	return PlayFabUsers.Num();
}

void AMultiplayerGameMode::UpdateConnectedPlayers()
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
