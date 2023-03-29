// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Core/PlayFabMultiplayerAPI.h"
#include "ServerTravelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLAYFABMULTIPLAYER_API AServerTravelGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	void GetMatchSuccess(const PlayFab::MultiplayerModels::FGetMatchResult& Result);
};
