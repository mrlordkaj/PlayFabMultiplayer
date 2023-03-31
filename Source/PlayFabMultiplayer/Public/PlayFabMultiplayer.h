// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "PlayFabBaseModel.h"
#include "PlayFabMultiplayer.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPlayFabMultiplayer, Log, All);

class FPlayFabMultiplayerModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

UCLASS()
class PLAYFABMULTIPLAYER_API UPlayFabMultiplayer : public UObject
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayFabGenericDelegate);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayFabMessageDelegate, FString, Message);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayFabErrorDelegate, FPlayFabError, ErrorResult);
};
