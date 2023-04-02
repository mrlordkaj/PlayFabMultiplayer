// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabAuthenticationContext.h"
#include "PlayFabBaseModel.h"
#include "GameFramework/Actor.h"
#include "PlayFab.h"
#include "Core/PlayFabClientAPI.h"
#include "PlayFabMultiplayer.h"
#include "PlayFabHelper.h"
#include "PlayFabBaseActor.generated.h"

UCLASS(DisplayName="PlayFab Base Actor")
class PLAYFABMULTIPLAYER_API APlayFabBaseActor : public AActor
{
	GENERATED_BODY()

protected:
	APlayFabBaseActor();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	UPlayFabMultiplayer::FPlayFabErrorDelegate OnPlayFabError;

protected:
	PlayFabClientPtr ClientAPI;

	PlayFab::FPlayFabErrorDelegate DefaultErrorCpp;

	/* Get PlayFabId stored in game instance. */
	FString GetLoginPlayFabId() { return UPlayFabHelper::GetLoginPlayFabId(this); }

	/* Get EntityId context stored in game instance. */
	FString GetLoginEntityId() { return UPlayFabHelper::GetLoginEntityId(this); }

	/* Get authentication context stored in game instance. */
	TSharedPtr<UPlayFabAuthenticationContext> GetLoginContext();

	/* Default PlayFabError event. */
	void PlayFabErrorCpp(const PlayFab::FPlayFabCppError& Error);

	/* Default PlayFabError event. */
	UFUNCTION(BlueprintCallable)
	void PlayFapError(FPlayFabError Error, UObject* CustomData);
};
