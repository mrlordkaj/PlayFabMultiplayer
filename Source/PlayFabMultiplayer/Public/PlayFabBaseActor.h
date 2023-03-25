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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegatePlayFabGeneric);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegatePlayFabMessage, FString, Message);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDelegatePlayFabError, FString, Name, FString, Message, int, Code);

	APlayFabBaseActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, DisplayName = "On PlayFab Error")
	FDelegatePlayFabError OnPlayFabError;

protected:
	PlayFabClientPtr ClientAPI;

	PlayFab::FPlayFabErrorDelegate DefaultErrorCpp;

	/* Get PlayFabId stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Get Login PlayFabId")
	FString GetLoginPlayFabId();

	/* Get authentication context stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Get Login EntityId")
	FString GetLoginEntityId();

	/* Get EntityId stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UPlayFabJsonObject* GetLoginEntityKey();

	/* Get authentication context stored in game instance. */
	TSharedPtr<UPlayFabAuthenticationContext> GetLoginContextCpp();

	/* Get authentication context stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UPlayFabAuthenticationContext* GetLoginContext();

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
