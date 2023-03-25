// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/PlayFabClientAPI.h"
#include "PlayFab.h"
#include "PlayFabBaseModel.h"
#include "PlayFabAuthenticationContext.h"
#include "PlayFabBaseComponent.generated.h"


UCLASS(DisplayName="PlayFab Base Component")
class PLAYFABMULTIPLAYER_API UPlayFabBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegatePlayFabGeneric);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegatePlayFabMessage, FString, Message);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDelegatePlayFabError, FString, Name, FString, Message, int, Code);

	UPlayFabBaseComponent();

protected:
	virtual void BeginPlay() override;

protected:
	PlayFabClientPtr ClientAPI;

	PlayFab::FPlayFabErrorDelegate DefaultErrorCpp;

	UPROPERTY(BlueprintAssignable, DisplayName = "On PlayFab Error")
	FDelegatePlayFabError OnPlayFabError;

	/* Gets PlayFabId stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Get Login PlayFabId")
	FString GetLoginPlayFabId();

	/* Gets EntityId stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Get Login EntityId")
	FString GetLoginEntityId();

	/* Generates EntityKey for blueprint usage. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Get Login EntityKey")
	UPlayFabJsonObject* GetLoginEntityKey();

	/* Gets authentication context stored in game instance. */
	TSharedPtr<UPlayFabAuthenticationContext> GetLoginContextCpp();

	/* Gets authentication context stored in game instance. */
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
