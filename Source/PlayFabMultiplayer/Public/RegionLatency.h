// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "RegionLatency.generated.h"

/**
 * https://docs.microsoft.com/en-us/rest/api/playfab/multiplayer/multiplayer-server/list-multiplayer-servers?view=playfab-rest
 */
USTRUCT(BlueprintType)
struct FRegionLatency
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	FString Region;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	float Latency;
};
