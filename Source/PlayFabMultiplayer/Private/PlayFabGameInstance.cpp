// Copyright (C) 2022 Thinh Pham.


#include "PlayFabGameInstance.h"
#include "PlayFabMultiplayer.h"
#include "PlayfabGSDK.h"
#include "GSDKUtils.h"

void UPlayFabGameInstance::Init()
{
	Super::Init();

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
	Super::OnStart();

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
	UE_LOG(PlayFabMultiplayer, Warning, TEXT("Server active"));
}

void UPlayFabGameInstance::OnGSDKReadyForPlayers()
{
	UE_LOG(PlayFabMultiplayer, Warning, TEXT("Server ready"));
}

void UPlayFabGameInstance::SetPlayFabLoginSession(FString PlayerId, UPlayFabJsonObject* PlayerEntity,
                                                  UPlayFabAuthenticationContext* AuthContext)
{
	PlayFabId = PlayerId;
	PlayFabEntity = PlayerEntity;
	PlayFabLoginContext = AuthContext;
}
