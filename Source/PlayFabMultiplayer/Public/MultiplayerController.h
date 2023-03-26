// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MultiplayerTypes.h"
#include "MultiplayerController.generated.h"

/**
 * 
 */
UCLASS()
class PLAYFABMULTIPLAYER_API AMultiplayerController : public APlayerController
{
	GENERATED_BODY()

public:
    virtual void PawnLeavingGame() override;

	UPROPERTY(BlueprintReadOnly)
    FString PawnClass;

    UPROPERTY(BlueprintReadOnly)
    FString PlayFabId;

    UPROPERTY(BlueprintReadOnly)
    FString TeamId;

protected:
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
    EPlayerLeaveBehaviour PlayerLeaveBehaviour = EPlayerLeaveBehaviour::DestroyPawn;

    virtual void OnPossess(APawn* aPawn) override;
};
