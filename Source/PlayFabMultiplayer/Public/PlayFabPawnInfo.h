#pragma once

#include "CoreMinimal.h"
#include "PlayFabPawnInfo.generated.h"

USTRUCT(BlueprintType)
struct FPlayFabPawnInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString PawnClass;

	UPROPERTY(BlueprintReadOnly)
	FString PlayFabId;
};
