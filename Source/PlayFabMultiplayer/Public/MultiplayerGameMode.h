// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabPawnInfo.h"
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
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void Logout(AController* ExitingPlayer) override;
	
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;
	
public:
	// /* Called server side when a player joined. */
	// void RegisterPlayFabUser(FString PlayFabId);
	//
	// /* Called server side when a player exited. */
	// void UnregisterPlayFabUser(FString PlayFabId);
	//
	// /* Count number of PlayFab users has been registered on server side. */
	// int GetNumPlayFabUsers() const;
	
private:
	// /* Store list of PlayFab players (PlayerId). */
	// TArray<FString> PlayFabUsers;

	/* Update connected players info on the PlayFab server. */
	void UpdateConnectedPlayers() const;

	TMap<AController*, FPlayFabPawnInfo> PlayFabPawnInfoMap;

protected:
	UPROPERTY(EditDefaultsOnly)
	bool ShutdownServerWhenNoPlayers = true;

	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSubclassOf<APawn>> PawnClassMap;

// private:
// 	UFUNCTION()
// 	void OnPlayerOut(AActor* PlayerController);
};
