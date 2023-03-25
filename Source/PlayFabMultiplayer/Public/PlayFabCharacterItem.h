// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayFabCharacterItem.generated.h"

/**
 * 
 */
UCLASS()
class PLAYFABMULTIPLAYER_API UPlayFabCharacterItem : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	FString ItemId;

	UPROPERTY(BlueprintReadOnly)
	FString DisplayName;

	UPROPERTY(BlueprintReadOnly)
	FString ImageURI;

	UPROPERTY(BlueprintReadOnly)
	float Price;

	UPROPERTY(BlueprintReadOnly)
	bool bOwned;
};
