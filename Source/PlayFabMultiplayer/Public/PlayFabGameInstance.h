// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlayFabAuthenticationContext.h"
#include "PlayFabJsonObject.h"
#include "PlayFab.h"
#include "Core/PlayFabClientAPI.h"
#include "PlayFabTypes.h"
#include "PlayFabGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLAYFABMULTIPLAYER_API UPlayFabGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void OnStart() override;

protected:
	UFUNCTION()
	void OnGSDKShutdown();

	UFUNCTION()
	bool OnGSDKHealthCheck();

	UFUNCTION()
	void OnGSDKServerActive();

	UFUNCTION()
	void OnGSDKReadyForPlayers();

public:
	/* The authentiacation context of login player. */
	TSharedPtr<UPlayFabAuthenticationContext> AuthenticationContext;

	/* The master id of login player. */
	FString PlayFabId;

	/* The title id of login player. */
	FString EntityId;
};
