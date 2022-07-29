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
	/* Store target map from client side. */
	UPROPERTY(BlueprintReadWrite)
	FString TravelTargetMap;

	/* Store player login context from client side. */
	UPROPERTY(BlueprintReadOnly)
	UPlayFabAuthenticationContext* PlayFabLoginContext;

	/* Store player title entity from client side. */
	UPROPERTY(BlueprintReadOnly)
	UPlayFabJsonObject* PlayFabEntity;

	/* Store PlayFabId from client side. */
	UPROPERTY(BlueprintReadOnly)
	FString PlayFabId;

	/* When player login successfully, register their session here. */
	UFUNCTION(BlueprintCallable, DisplayName = "Set PlayFab Session")
	void SetPlayFabLoginSession(FString PlayerId, UPlayFabJsonObject* PlayerEntity,
	                            UPlayFabAuthenticationContext* AuthContext);

	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Get PlayFab Session")
	void GetPlayFabLoginSession(FString& PlayerId, UPlayFabJsonObject* & PlayerEntity,
	                            UPlayFabAuthenticationContext* & AuthContext);
};
