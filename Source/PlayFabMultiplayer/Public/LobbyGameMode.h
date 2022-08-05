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

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
	                      FString& ErrorMessage) override;
	
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal,
	                                 const FString& Options, const FUniqueNetIdRepl& UniqueId,
	                                 FString& ErrorMessage) override;

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
