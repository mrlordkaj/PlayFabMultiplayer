// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabAuthenticationContext.h"
#include "PlayFabBaseModel.h"
#include "GameFramework/Actor.h"
#include "PlayFab.h"
#include "Core/PlayFabClientAPI.h"
#include "PlayFabBaseActor.generated.h"

UCLASS(DisplayName="PlayFab Base Actor")
class PLAYFABMULTIPLAYER_API APlayFabBaseActor : public AActor
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGenericDelegate);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGenericMessage, FString, Message);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDelegateOnPlayFabError, FString, Name, FString, Message, int, Code);

	APlayFabBaseActor();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, DisplayName = "On PlayFab Error")
	FDelegateOnPlayFabError OnPlayFabError;

protected:
	PlayFabClientPtr ClientAPI;

	PlayFab::FPlayFabErrorDelegate DefaultErrorDelegate;

	/* Get player's PlayFabId stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Get PlayFabId")
	FString GetPlayFabId();

	/* Get authentication context stored in game instance. */
	FString GetEntityId();

	/* Get player's entity stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UPlayFabJsonObject* GetEntityKey();

	/* Get authentication context stored in game instance. */
	TSharedPtr<UPlayFabAuthenticationContext> GetAuthenticationContextCpp();

	/* Get authentication context stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UPlayFabAuthenticationContext* GetAuthenticationContext();

	/* Default PlayFabError event. */
	void PlayFabErrorCpp(const PlayFab::FPlayFabCppError& Error);

	/* Default PlayFabError event. */
	UFUNCTION(BlueprintCallable)
	void PlayFapError(FPlayFabError Error, UObject* CustomData);

public:
	/* Checks current login status. */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasLogin();
};
