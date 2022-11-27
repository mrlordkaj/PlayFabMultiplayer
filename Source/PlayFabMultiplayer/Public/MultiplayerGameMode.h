// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerController.h"
#include "GameFramework/GameModeBase.h"
#include "MultiplayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLAYFABMULTIPLAYER_API AMultiplayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMultiplayerGameMode();

	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal,
	                                 const FString& Options, const FUniqueNetIdRepl& UniqueId,
	                                 FString& ErrorMessage) override;
	
	virtual void Logout(AController* ExitingPlayer) override;
	
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	
private:
	/* Store connected players. */
	UPROPERTY()
	TArray<AMultiplayerController*> ConnectedPlayers;
	
	/* Update connected players info on the PlayFab server. */
	void UpdateConnectedPlayers() const;

protected:
	/* The limiation of number players can join. */
	UPROPERTY(EditDefaultsOnly)
	uint8 MaximumPlayers = 0;

	/* Should the server auto-shutdown when the last player left game. */
	UPROPERTY(EditDefaultsOnly)
	bool ShutdownServerWhenNoPlayers = true;

	/* Define classes for player spawn at start or respawn in game. */
	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSubclassOf<APawn>> PawnClassMap;
};
