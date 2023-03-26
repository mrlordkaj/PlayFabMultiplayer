// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/PlayFabClientAPI.h"
#include "PlayFabMultiplayer.h"
#include "PlayFab.h"
#include "PlayFabBaseModel.h"
#include "PlayFabAuthenticationContext.h"
#include "PlayFabBaseComponent.generated.h"


UCLASS(DisplayName="PlayFab Base Component")
class PLAYFABMULTIPLAYER_API UPlayFabBaseComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPlayFabBaseComponent();

	virtual void BeginPlay() override;

protected:
	PlayFabClientPtr ClientAPI;

	PlayFab::FPlayFabErrorDelegate DefaultErrorCpp;

	UPROPERTY(BlueprintAssignable)
	UPlayFabMultiplayer::FPlayFabErrorDelegate OnPlayFabError;

	/* Gets PlayFabId stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Get Login PlayFabId")
	FString GetLoginPlayFabId();

	/* Gets EntityId stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Get Login EntityId")
	FString GetLoginEntityId();

	/* Gets authentication context stored in game instance. */
	TSharedPtr<UPlayFabAuthenticationContext> GetLoginContextCpp();

	/* Default PlayFabError event. */
	void PlayFabErrorCpp(const PlayFab::FPlayFabCppError& Error);

	/* Default PlayFabError event. */
	UFUNCTION(BlueprintCallable)
	void PlayFapError(FPlayFabError Error, UObject* CustomData);
};
