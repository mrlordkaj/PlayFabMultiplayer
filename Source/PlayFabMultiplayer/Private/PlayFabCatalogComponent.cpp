// Copyright (C) 2022 Thinh Pham.


#include "PlayFabCatalogComponent.h"
#include "PlayFabHelper.h"

using namespace PlayFab::ClientModels;

void UPlayFabCatalogComponent::GetCatalogItems()
{
	FGetCatalogItemsRequest R;
	R.AuthenticationContext = GetLoginContext();
	R.CatalogVersion = CatalogVersion;
	UE_LOG(LogPlayFabMultiplayer, Warning, TEXT("GetCatalogItems: %s"), *R.toJSONString());
	ClientAPI->GetCatalogItems(R,
		PlayFab::UPlayFabClientAPI::FGetCatalogItemsDelegate::CreateUObject(this, &UPlayFabCatalogComponent::GetCatalogItemsSuccess),
		DefaultErrorCpp);
}

void UPlayFabCatalogComponent::GetCatalogItemsSuccess(const FGetCatalogItemsResult& Result)
{
	UE_LOG(LogPlayFabMultiplayer, Display, TEXT("GetCatalogItems: %s"), *Result.toJSONString());
	Items.Empty();
	for (FCatalogItem I : Result.Catalog)
	{
		FName Name(I.ItemId);
		if (!BlacklistItems.Contains(Name))
		{
			Items.Add(I);
		}
	}
	OnGetCatalogItemsSuccess.Broadcast();
}

void UPlayFabCatalogComponent::PurchaseItem(FString ItemId, FString Currency)
{
	for (FCatalogItem I : Items)
	{
		if (I.ItemId == ItemId) {
			FPurchaseItemRequest R;
			R.AuthenticationContext = GetLoginContext();
			R.CatalogVersion = CatalogVersion;
			R.ItemId = ItemId;
			R.VirtualCurrency = Currency;
			R.Price = UPlayFabHelper::ReadItemPrice(I, Currency);
			UE_LOG(LogPlayFabMultiplayer, Warning, TEXT("PurchaseItem: %s"), *R.toJSONString());
			ClientAPI->PurchaseItem(R,
				PlayFab::UPlayFabClientAPI::FPurchaseItemDelegate::CreateUObject(this, &UPlayFabCatalogComponent::PurchaseItemSuccess),
				DefaultErrorCpp);
			return;
		}
	}
}

void UPlayFabCatalogComponent::PurchaseItemSuccess(const FPurchaseItemResult& Result)
{
	UE_LOG(LogPlayFabMultiplayer, Display, TEXT("PurchaseItem: %s"), *Result.toJSONString());
	if (!Result.Items.IsEmpty())
	{
		FItemInstance I = Result.Items[0];
		OnPurchaseItemSuccess.Broadcast(FName(I.ItemId), I.ItemClass, I.UnitCurrency, I.UnitPrice);
	}
}
