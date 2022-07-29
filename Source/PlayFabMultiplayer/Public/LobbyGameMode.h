// Copyright (C) 2022 Thinh Pham.

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

	void SetTargetMap(const FString ClientTargetMap);

protected:
	/* Delay before travel to target map, in seconds. */
	UPROPERTY(EditDefaultsOnly)
	int TravelDelay = 10;

private:
	/* The target map to be travelled to. */
	FString TargetMap;

	/* Travel command called after the delay. */
	void TravelTargetMap() const;
};
