// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayFabGameMode.h"
#include "PlayFabUserComponent.h"
#include "PlayFabMultiplayer.h"
#include "Kismet/KismetSystemLibrary.h"
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

	if (HasAuthority() && ShutdownServerWhenNoPlayers) {
		ExitingPlayer->OnDestroyed.AddDynamic(this, &APlayFabGameMode::OnPlayerLeft);
	}
}

void APlayFabGameMode::OnPlayerLeft(AActor* Controller)
{
	if (GetNumPlayers() < 1) {
		RequestEngineExit("All players left");
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

void APlayFabGameMode::UpdateConnectedPlayers()
{
	TArray<FConnectedPlayer> Players;
	for (FString PlayerId : PlayFabUsers) {
		FConnectedPlayer Player;
		Player.PlayerId = PlayerId;
		Players.Add(Player);
	}
	UE_LOG(PlayFabMultiplayer, Warning, TEXT("Total PlayFabUser(s): %d"), Players.Num());
	UGSDKUtils::UpdateConnectedPlayers(Players);
}
