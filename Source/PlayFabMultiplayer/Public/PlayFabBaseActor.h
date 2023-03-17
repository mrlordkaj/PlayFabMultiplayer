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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnErrorMessage, FString, Message);

public:
	APlayFabBaseActor();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
	FOnErrorMessage OnErrorMessage;

private:
	PlayFab::ClientModels::FLoginResult GetLoginResult();

protected:
	PlayFabClientPtr ClientAPI;

	UFUNCTION(BlueprintCallable, DisplayName="PlayFab Error")
	void PlayFapError(FPlayFabError Error, UObject* CustomData);

	/* Get player's authentication context stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName="Get PlayFabAuth")
	UPlayFabAuthenticationContext* GetLoginContext();

	/* Get player's entity stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName="Get PlayFabEntity")
	UPlayFabJsonObject* GetPlayFabEntity();

	/* Get player's PlayFabId stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName="Get PlayFabId")
	FString GetPlayFabId();

public:
	void OnError(const PlayFab::FPlayFabCppError& ErrorResult) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsLoggingIn();
};
