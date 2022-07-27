// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Controller.h"
#include "PlayFabGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLAYFABMULTIPLAYER_API APlayFabGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	APlayFabGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* ExitingPlayer) override;

public:
	/* Called server side when a player joined. */
	void RegisterPlayFabUser(FString PlayerId);

	/* Called server side when a player exited. */
	void UnregisterPlayFabUser(FString PlayerId);

	int GetNumPlayFabUsers() const;

private:
	/* Store list of PlayFab players (PlayerId). */
	TArray<FString> PlayFabUsers;

	/* Update connected players info on the PlayFab server. */
	void UpdateConnectedPlayers();

protected:
	UPROPERTY(EditDefaultsOnly)
	bool ShutdownServerWhenNoPlayers = true;

private:
	UFUNCTION()
	void OnPlayerLeft(AActor* Controller);
};
