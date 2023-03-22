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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDelegateOnPlayFabError, FString, Name, FString, Message, int, Code);

	UPlayFabBaseComponent();

protected:
	virtual void BeginPlay() override;

protected:
	PlayFabClientPtr ClientAPI;

	PlayFab::FPlayFabErrorDelegate DefaultErrorCpp;

	UPROPERTY(BlueprintAssignable, DisplayName = "On PlayFab Error")
	FDelegateOnPlayFabError OnPlayFabError;

	/* Gets PlayFabId stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Get MyMasterId")
	FString GetMyMasterId();

	/* Gets EntityId stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Get MyEntityId")
	FString GetMyEntityId();

	/* Generates EntityKey for blueprint usage. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Get MyEntityKey")
	UPlayFabJsonObject* GetMyEntityKey();

	/* Gets authentication context stored in game instance. */
	TSharedPtr<UPlayFabAuthenticationContext> GetAuthenticationContextCpp();

	/* Gets authentication context stored in game instance. */
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
