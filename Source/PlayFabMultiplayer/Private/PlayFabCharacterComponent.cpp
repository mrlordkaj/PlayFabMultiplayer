// Copyright (C) 2022 Thinh Pham.


#include "PlayFabCharacterComponent.h"

using namespace PlayFab::ClientModels;

void UPlayFabCharacterComponent::ListCatalogCharacters()
{
	FExecuteCloudScriptRequest R;
	R.AuthenticationContext = GetLoginContext();
	R.FunctionName = TEXT("ListCatalogCharacters");
	TSharedPtr<FJsonObject> J = MakeShareable(new FJsonObject);
	J->SetStringField(TEXT("CatalogVersion"), CatalogVersion);
	R.FunctionParameter = PlayFab::FJsonKeeper(J);
	UE_LOG(LogPlayFabMultiplayer, Warning, TEXT("%s"), *R.toJSONString());
	ClientAPI->ExecuteCloudScript(R,
		PlayFab::UPlayFabClientAPI::FExecuteCloudScriptDelegate::CreateUObject(this, &UPlayFabCharacterComponent::ListCatalogCharactersSuccess),
		DefaultErrorCpp);
}

void UPlayFabCharacterComponent::ListCatalogCharactersSuccess(const FExecuteCloudScriptResult& Result)
{
	UE_LOG(LogPlayFabMultiplayer, Display, TEXT("%s"), *Result.toJSONString());
}

void UPlayFabCharacterComponent::PurchaseCharacter(FString ItemId, FString Currency, int Price, FString Name, FPurchaseCharacterSuccess OnSuccess)
{
	OnPurchaseCharacterSuccess = OnSuccess;
	PurchaseCharacterName = Name;
	FPurchaseItemRequest R;
	R.AuthenticationContext = GetLoginContext();
	R.ItemId = ItemId;
	R.Price = Price;
	R.VirtualCurrency = Currency;
	R.CatalogVersion = CatalogVersion;
	UE_LOG(LogTemp, Warning, TEXT("PurchaseItem: %s"), *R.toJSONString());
	ClientAPI->PurchaseItem(R,
		PlayFab::UPlayFabClientAPI::FPurchaseItemDelegate::CreateUObject(this, &UPlayFabCharacterComponent::PurchaseCharacterTokenSuccess),
		DefaultErrorCpp);
}

void UPlayFabCharacterComponent::PurchaseCharacterTokenSuccess(const FPurchaseItemResult& Result)
{
	UE_LOG(LogTemp, Display, TEXT("PurchaseItem: %s"), *Result.toJSONString());
	FItemInstance Item = Result.Items[0];
	FGrantCharacterToUserRequest R;
	R.AuthenticationContext = GetLoginContext();
	R.CatalogVersion = CatalogVersion;
	R.CharacterName = PurchaseCharacterName.IsEmpty() ? Item.DisplayName : PurchaseCharacterName;
	R.ItemId = Item.ItemId;
	UE_LOG(LogTemp, Warning, TEXT("GrantCharacterToUser: %s"), *R.toJSONString());
	ClientAPI->GrantCharacterToUser(R,
		PlayFab::UPlayFabClientAPI::FGrantCharacterToUserDelegate::CreateUObject(this, &UPlayFabCharacterComponent::PurchaseCharacterSuccess),
		DefaultErrorCpp);
}

void UPlayFabCharacterComponent::PurchaseCharacterSuccess(const FGrantCharacterToUserResult& Result)
{
	UE_LOG(LogTemp, Display, TEXT("GrantCharacterToUser: %s"), *Result.toJSONString());
	OnPurchaseCharacterSuccess.Execute();
}
