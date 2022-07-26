// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlayFabAuthenticationContext.h"
#include "ConnectedPlayer.h"
#include "PlayFabGameInstance.generated.h"

//DECLARE_LOG_CATEGORY_EXTERN(LogPlayFab, Log, All);

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

    /* Store player title id from client side. */
    UPROPERTY(BlueprintReadWrite)
    FString PlayerId;
};
