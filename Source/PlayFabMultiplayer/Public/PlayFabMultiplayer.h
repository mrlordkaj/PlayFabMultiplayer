// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(PlayFabMultiplayer, Log, All);

class FPlayFabMultiplayerModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
