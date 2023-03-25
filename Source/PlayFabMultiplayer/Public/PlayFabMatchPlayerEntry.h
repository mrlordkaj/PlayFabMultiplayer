// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayFabMatchPlayerEntry.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PLAYFABMULTIPLAYER_API UPlayFabMatchPlayerEntry : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString DisplayName;

	UPROPERTY(BlueprintReadOnly)
	FString AvatarUrl;

	UPROPERTY(BlueprintReadOnly)
	FString Position;
};
