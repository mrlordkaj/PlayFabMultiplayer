// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
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

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* ExitingPlayer) override;

public:
	/* Called server side when a player joined. */
	void RegisterPlayFabUser(FString PlayerId);

	/* Called server side when a player exited. */
	void UnregisterPlayFabUser(FString PlayerId);

	/* Count number of PlayFab users has been registered on server side. */
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
	void OnPlayerOut(AActor* PlayerController);
};
