// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLAYFABMULTIPLAYER_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ALobbyGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Tick(float DeltaTime) override;

	/* Delay before travel to target map, in seconds. */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float TravelDelay = 5;

private:

	APlayerController* FirstController = nullptr;
	FString ServerTargetMap;
	float TravelCooldown = -1;
};
