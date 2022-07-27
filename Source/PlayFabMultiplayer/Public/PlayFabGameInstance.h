// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
//#include "PlayFabClientModels.h"
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
    FString ServerTargetMap;

    /* Store player login context from client side. */
    UPROPERTY(BlueprintReadOnly)
    UPlayFabAuthenticationContext* PlayFabLoginContext;

    /* Store player title entity from client side. */
    UPROPERTY(BlueprintReadOnly)
    UPlayFabJsonObject* PlayFabLoginEntity;

    /* Store player title id from client side. Deprecated, use PlayFabLoginEntity instead. */
    UPROPERTY(BlueprintReadOnly)
    FString PlayFabMasterId;

    /* When player login successfully, register their session here. */
    UFUNCTION(BlueprintCallable)
    void SetPlayFabLoginSession(FString PlayFabId, UPlayFabJsonObject* Entity, UPlayFabAuthenticationContext* Context);

    //UPROPERTY(BlueprintReadWrite)
    //FClientLoginResult PlayFabLoginResult;
};
