// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "LobbyPawn.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

ALobbyGameMode::ALobbyGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = ALobbyPawn::StaticClass();
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// register first player, to read target map later
	if (!FirstController && HasAuthority()) {
		FirstController = NewPlayer;
	}
}

void ALobbyGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// try to read target map from first player
	if (FirstController && ServerTargetMap.IsEmpty() && HasAuthority()) {
		APawn* Pawn = FirstController->GetPawn();
		ALobbyPawn* LobbyPawn = Cast<ALobbyPawn>(Pawn);
		if (LobbyPawn) {
			ServerTargetMap = LobbyPawn->ServerTargetMap;
			if (!ServerTargetMap.IsEmpty()) {
				TravelCooldown = TravelDelay;
			}
		}
	}

	// delay few seconds before travel to target map
	if (TravelCooldown >= 0) {
		TravelCooldown -= DeltaTime;
		if (TravelCooldown < 0) {
			FString Command = "servertravel " + ServerTargetMap;
			UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), Command);
		}
	}
}