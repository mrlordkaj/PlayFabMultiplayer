// Copyright (C) 2022 Thinh Pham.


#include "MultiplayerController.h"
#include "MultiplayerUserComponent.h"

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
