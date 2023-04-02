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

public:
	/* Error multicast delegate for blueprint usage. */
	UPROPERTY(BlueprintAssignable)
	UPlayFabMultiplayer::FPlayFabErrorDelegate OnPlayFabError;

protected:
	/* Common client api pointer. */
	PlayFabClientPtr ClientAPI;

	/* Default error delegate for cpp uage. */
	PlayFab::FPlayFabErrorDelegate DefaultErrorCpp;

	/* Gets PlayFabId stored in game instance. */
	FString GetLoginPlayFabId() { return UPlayFabHelper::GetLoginPlayFabId(this); }

	/* Gets EntityId stored in game instance. */
	FString GetLoginEntityId() { return UPlayFabHelper::GetLoginEntityId(this); }

	/* Gets authentication context stored in game instance. */
	TSharedPtr<UPlayFabAuthenticationContext> GetLoginContext();

	/* Default error event for cpp usage. */
	void PlayFabErrorCpp(const PlayFab::FPlayFabCppError& Error);

	/* Default error event for blueprint usage. */
	UFUNCTION(BlueprintCallable)
	void PlayFapError(FPlayFabError Error, UObject* CustomData);
};
