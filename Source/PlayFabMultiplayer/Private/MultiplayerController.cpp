// Copyright (C) 2022 Thinh Pham.


#include "MultiplayerController.h"
#include "MultiplayerUserComponent.h"

void AMultiplayerController::PawnLeavingGame()
{
	switch (PlayerLeaveBehaviour)
	{
	case EPlayerLeaveBehaviour::DestroyPawn:
		Super::PawnLeavingGame();
		return;

	case EPlayerLeaveBehaviour::PossesAI:
		if (APawn* P = GetPawn())
		{
			if (AController* AI = GetWorld()->SpawnActor<AController>(P->AIControllerClass)) {
				AI->Possess(P);
			}
			SetPawn(NULL);
		}
		return;

	case EPlayerLeaveBehaviour::DoNothing:
		if (GetPawn())
		{
			SetPawn(NULL);
		}
		return;
	}
}

void AMultiplayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	TArray<UMultiplayerUserComponent*> Users;
	aPawn->GetComponents(Users);
	for (UMultiplayerUserComponent* User : Users)
	{
		User->PlayFabId = PlayFabId;
		User->TeamId = TeamId;
	}
}
