// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlayFabAuthenticationContext.h"
#include "PlayFabJsonObject.h"
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
	/* Store player login context from client side. */
	UPROPERTY()
	UPlayFabAuthenticationContext* PlayFabLoginContext;

	/* Store player title entity from client side. */
	UPROPERTY()
	UPlayFabJsonObject* PlayFabEntity;

	/* Store PlayFabId from client side. */
	UPROPERTY()
	FString PlayFabId;

	/* When player login successfully, register their session here. */
	UFUNCTION(BlueprintCallable, DisplayName = "Set PlayFab Session")
	void SetPlayFabLoginSession(FString PlayerId, UPlayFabJsonObject* PlayerEntity,
	                            UPlayFabAuthenticationContext* AuthContext);
};
