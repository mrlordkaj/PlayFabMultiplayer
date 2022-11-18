// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "MultiplayerTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MultiplayerHelper.generated.h"

/**
 * 
 */
UCLASS()
class PLAYFABMULTIPLAYER_API UMultiplayerHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Multiplayer")
	static ETeamStatus CheckTeamStatus(AActor* A, AActor* B);
};
