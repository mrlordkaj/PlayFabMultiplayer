// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabBaseComponent.h"
#include "PlayFabCatalogComponent.generated.h"

/**
 * 
 */
UCLASS()
class PLAYFABMULTIPLAYER_API UPlayFabCatalogComponent : public UPlayFabBaseComponent
{
	GENERATED_BODY()

protected:
	/* The catalog version. Leave blank for default catalog. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString CatalogVersion;
	
public:
	UFUNCTION(BlueprintCallable)
	void GetCatalogItems();

private:
	void GetCatalogItemsSuccess(const PlayFab::ClientModels::FGetCatalogItemsResult& Result);
};
