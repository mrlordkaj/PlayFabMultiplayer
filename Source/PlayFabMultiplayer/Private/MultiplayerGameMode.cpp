// Copyright (C) 2022 Thinh Pham.


#include "MultiplayerGameMode.h"
#include "PlayFabMultiplayer.h"
#include "GSDKUtils.h"
#include "PlayFabUserComponent.h"
#include "Kismet/GameplayStatics.h"

AMultiplayerGameMode::AMultiplayerGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMultiplayerGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
	FString& ErrorMessage)
{
	// TODO: accept or reject player
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

APlayerController* AMultiplayerGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal,
	const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* Controller = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	// TODO: get team
	FPlayFabPawnInfo Info;
	Info.PawnClass = UGameplayStatics::ParseOption(Options, "PawnClass");
	Info.PlayFabId = UGameplayStatics::ParseOption(Options, "PlayFabId");
	PlayFabPawnInfoMap.Add(Controller, Info);
	UpdateConnectedPlayers();
	
	return Controller;
}

void AMultiplayerGameMode::Logout(AController* ExitingPlayer)
{
	Super::Logout(ExitingPlayer);

	PlayFabPawnInfoMap.Remove(ExitingPlayer);
	UpdateConnectedPlayers();
	
#if UE_SERVER
	if (ShutdownServerWhenNoPlayers && PlayFabPawnInfoMap.Num() < 1)
	{
		FPlatformMisc::RequestExit(false);
	}
	
	// if (ShutdownServerWhenNoPlayers) {
	// 	ExitingPlayer->OnDestroyed.AddDynamic(this, &APlayFabGameMode::OnPlayerOut);
	// }
#endif
}

UClass* AMultiplayerGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (const FPlayFabPawnInfo* Info = PlayFabPawnInfoMap.Find(InController))
	{
		if (const TSubclassOf<APawn>* PawnClass = PawnClassMap.Find(Info->PawnClass))
		{
			return Cast<UClass>(PawnClass->Get());
		}
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

APawn* AMultiplayerGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer,
	const FTransform& SpawnTransform)
{
	APawn* Pawn = Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);

	if (const FPlayFabPawnInfo* Info = PlayFabPawnInfoMap.Find(NewPlayer))
	{
		TArray<UPlayFabUserComponent*> Users;
		Pawn->GetComponents(Users);
		for (UPlayFabUserComponent* User : Users)
		{
			User->PlayFabId = Info->PlayFabId;
		}
	}
	
	return Pawn;
}

// void AMultiplayerGameMode::OnPlayerOut(AActor* PlayerController)
// {
// 	if (GetNumPlayers() < 1)
// 	{
// 		FPlatformMisc::RequestExit(false);
// 	}
// }

// void AMultiplayerGameMode::RegisterPlayFabUser(FString PlayFabId)
// {
// 	UE_LOG(PlayFabMultiplayer, Warning, TEXT("PlayFabUser joined: %s"), *PlayFabId);
// 	PlayFabUsers.AddUnique(PlayFabId);
// 	UpdateConnectedPlayers();
// }
//
// void AMultiplayerGameMode::UnregisterPlayFabUser(FString PlayFabId)
// {
// 	UE_LOG(PlayFabMultiplayer, Warning, TEXT("PlayFabUser exited: %s"), *PlayFabId);
// 	PlayFabUsers.Remove(PlayFabId);
// 	UpdateConnectedPlayers();
// }
//
// int AMultiplayerGameMode::GetNumPlayFabUsers() const
// {
// 	return PlayFabUsers.Num();
// }

void AMultiplayerGameMode::UpdateConnectedPlayers() const
{
	// TArray<FConnectedPlayer> Players;
	// for (FString PlayerId : PlayFabUsers)
	// {
	// 	FConnectedPlayer Player;
	// 	Player.PlayerId = PlayerId;
	// 	Players.Add(Player);
	// }
	// UE_LOG(PlayFabMultiplayer, Warning, TEXT("Total PlayFabUser(s): %d"), Players.Num());
	// UGSDKUtils::UpdateConnectedPlayers(Players);

	TArray<FPlayFabPawnInfo> Infos;
	PlayFabPawnInfoMap.GenerateValueArray(Infos);
	TArray<FConnectedPlayer> Players;
	for (FPlayFabPawnInfo Info : Infos)
	{
		FConnectedPlayer Player;
		Player.PlayerId = Info.PlayFabId;
		Players.Add(Player);
	}
	UE_LOG(PlayFabMultiplayer, Warning, TEXT("Total PlayFabUser(s): %d"), Players.Num());
	UGSDKUtils::UpdateConnectedPlayers(Players);
}
