// Copyright (C) 2022 Thinh Pham.


#include "MultiplayerGameMode.h"
#include "GSDKUtils.h"
#include "MultiplayerController.h"
#include "PlayFabMultiplayer.h"
#include "MultiplayerUserComponent.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"


AMultiplayerGameMode::AMultiplayerGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
	PlayerControllerClass = AMultiplayerController::StaticClass();
}

APlayerController* AMultiplayerGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal,
	const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	if (MaximumPlayers > 0 && GetNumPlayers() >= MaximumPlayers) {
		ErrorMessage = "Reached maximum players.";
	}
	if (!ErrorMessage.IsEmpty()) {
		return nullptr;
	}
	APlayerController* Controller = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	if (AMultiplayerController* MC = Cast<AMultiplayerController>(Controller))
	{
		MC->PlayFabId = UGameplayStatics::ParseOption(Options, "PlayFabId");
		MC->PawnClass = UGameplayStatics::ParseOption(Options, "PawnClass");
		MC->TeamId = Portal;
		ConnectedPlayers.AddUnique(MC);
		UpdateConnectedPlayers();
	}
	return Controller;
}

void AMultiplayerGameMode::Logout(AController* ExitingPlayer)
{
	Super::Logout(ExitingPlayer);

	ConnectedPlayers.Remove(Cast<AMultiplayerController>(ExitingPlayer));
	UpdateConnectedPlayers();
	
#if UE_SERVER
	if (ShutdownServerWhenNoPlayers && ConnectedPlayers.Num() < 1)
	{
		FPlatformMisc::RequestExit(false);
	}
#endif
}

UClass* AMultiplayerGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (const AMultiplayerController* MC = Cast<AMultiplayerController>(InController))
	{
		if (const TSubclassOf<APawn>* PawnClass = PawnClassMap.Find(MC->PawnClass))
		{
			return PawnClass->Get();
		}
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

APawn* AMultiplayerGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer,
	const FTransform& SpawnTransform)
{
	APawn* Pawn = Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);
	if (const AMultiplayerController* MC = Cast<AMultiplayerController>(NewPlayer))
	{
		TArray<UMultiplayerUserComponent*> Users;
		Pawn->GetComponents(Users);
		for (UMultiplayerUserComponent* User : Users)
		{
			User->PlayFabId = MC->PlayFabId;
			User->TeamId = MC->TeamId;
		}
	}
	return Pawn;
}

void AMultiplayerGameMode::UpdateConnectedPlayers() const
{
	TArray<FConnectedPlayer> Players;
	for (AMultiplayerController* MC : ConnectedPlayers)
	{
		if (!MC->PlayFabId.IsEmpty())
		{
			FConnectedPlayer Player;
			Player.PlayerId = MC->PlayFabId;
			Players.Add(Player);
		}
	}
	UE_LOG(PlayFabMultiplayer, Display, TEXT("Connected Player(s): %d"), Players.Num());
	UGSDKUtils::UpdateConnectedPlayers(Players);
}
