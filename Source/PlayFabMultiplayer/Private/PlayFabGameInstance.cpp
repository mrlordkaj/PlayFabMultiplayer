// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayFabGameInstance.h"
#include "PlayFabMultiplayer.h"
#include "PlayfabGSDK.h"
#include "GSDKUtils.h"
#include "PlayFab.h"

void UPlayFabGameInstance::Init()
{
    FOnGSDKShutdown_Dyn OnGsdkShutdown;
    OnGsdkShutdown.BindDynamic(this, &UPlayFabGameInstance::OnGSDKShutdown);
    FOnGSDKHealthCheck_Dyn OnGsdkHealthCheck;
    OnGsdkHealthCheck.BindDynamic(this, &UPlayFabGameInstance::OnGSDKHealthCheck);
    FOnGSDKServerActive_Dyn OnGSDKServerActive;
    OnGSDKServerActive.BindDynamic(this, &UPlayFabGameInstance::OnGSDKServerActive);
    FOnGSDKReadyForPlayers_Dyn OnGSDKReadyForPlayers;
    OnGSDKReadyForPlayers.BindDynamic(this, &UPlayFabGameInstance::OnGSDKReadyForPlayers);

    UGSDKUtils::RegisterGSDKShutdownDelegate(OnGsdkShutdown);
    UGSDKUtils::RegisterGSDKHealthCheckDelegate(OnGsdkHealthCheck);
    UGSDKUtils::RegisterGSDKServerActiveDelegate(OnGSDKServerActive);
    UGSDKUtils::RegisterGSDKReadyForPlayers(OnGSDKReadyForPlayers);

#if UE_SERVER
    UGSDKUtils::SetDefaultServerHostPort();
#endif
}

void UPlayFabGameInstance::OnStart()
{
    UGSDKUtils::ReadyForPlayers();
}

void UPlayFabGameInstance::OnGSDKShutdown()
{
    UE_LOG(PlayFabMultiplayer, Warning, TEXT("Server shutdown"));
    FPlatformMisc::RequestExit(false);
}

bool UPlayFabGameInstance::OnGSDKHealthCheck()
{
    return true;
}

void UPlayFabGameInstance::OnGSDKServerActive()
{
    /**
     * Server is transitioning to an active state.
     * Optional: Add in the implementation any code that is needed for the game server when
     * this transition occurs.
     */
    UE_LOG(PlayFabMultiplayer, Warning, TEXT("Server active"));
}

void UPlayFabGameInstance::OnGSDKReadyForPlayers()
{
    /**
     * Server is transitioning to a StandBy state. Game initialization is complete and the game is ready
     * to accept players.
     * Optional: Add in the implementation any code that is needed for the game server before
     * initialization completes.
     */
    UE_LOG(PlayFabMultiplayer, Warning, TEXT("Server ready"));
}
