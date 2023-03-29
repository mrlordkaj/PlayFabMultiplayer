// Copyright (C) 2022 Thinh Pham.


#include "PlayFabCatalogComponent.h"

using namespace PlayFab::ClientModels;

void UPlayFabCatalogComponent::GetCatalogItems()
{
	FGetCatalogItemsRequest R;
	R.AuthenticationContext = GetLoginContext();
	if (!CatalogVersion.IsEmpty()) {
		R.CatalogVersion = CatalogVersion;
	}
	UE_LOG(LogPlayFabMultiplayer, Warning, TEXT("GetCatalogItems: %s"), *R.toJSONString());
	ClientAPI->GetCatalogItems(R,
		PlayFab::UPlayFabClientAPI::FGetCatalogItemsDelegate::CreateUObject(this, &UPlayFabCatalogComponent::GetCatalogItemsSuccess),
		DefaultErrorCpp);
}

void UPlayFabCatalogComponent::GetCatalogItemsSuccess(const FGetCatalogItemsResult& Result)
{
	UE_LOG(LogPlayFabMultiplayer, Display, TEXT("GetCatalogItems: %s"), *Result.toJSONString());
}
