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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FPurchaseItemSuccessDelegate, FName, ItemId, FString, ItemClass, FString, UnitCurrency, int, UnitPrice);

public:
	UPROPERTY(BlueprintAssignable)
	UPlayFabMultiplayer::FPlayFabGenericDelegate OnGetCatalogItemsSuccess;

	UPROPERTY(BlueprintAssignable)
	FPurchaseItemSuccessDelegate OnPurchaseItemSuccess;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CatalogVersion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> BlacklistItems;

	TArray<PlayFab::ClientModels::FCatalogItem> Items;

	UFUNCTION(BlueprintCallable)
	void GetCatalogItems();

	UFUNCTION(BlueprintCallable)
	void PurchaseItem(FString ItemId, FString Currency);

private:
	void GetCatalogItemsSuccess(const PlayFab::ClientModels::FGetCatalogItemsResult& Result);

	void PurchaseItemSuccess(const PlayFab::ClientModels::FPurchaseItemResult& Result);
};
