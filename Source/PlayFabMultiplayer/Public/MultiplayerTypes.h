// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerTypes.generated.h"

UENUM(BlueprintType, DisplayName="Team Status")
enum class ETeamStatus : uint8 {
	Ally, Enemy, Neutral, Itself, Invalid
};

UENUM(BlueprintType, DisplayName = "Player Leave Behaviour")
enum class EPlayerLeaveBehaviour : uint8 {
	DestroyPawn, PossesAI, DoNothing
};
