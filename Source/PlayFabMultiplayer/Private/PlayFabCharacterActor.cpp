// Copyright (C) 2022 Thinh Pham.


#include "PlayFabCharacterActor.h"
#include "Kismet/KismetSystemLibrary.h"

using namespace PlayFab::ClientModels;

void APlayFabCharacterActor::GetCatalogCharacters()
{
	// clear current characters
	Characters.Empty();
	// call API
	FGetCatalogItemsRequest Request;
	Request.AuthenticationContext = GetLoginContextCpp();
	Request.CatalogVersion = CatalogVersion;
	ClientAPI->GetCatalogItems(Request,
		PlayFab::UPlayFabClientAPI::FGetCatalogItemsDelegate::CreateUObject(this, &APlayFabCharacterActor::OnGetCatalogCharactersSuccess),
		DefaultErrorCpp);
}

void APlayFabCharacterActor::OnGetCatalogCharactersSuccess(const FGetCatalogItemsResult& Result)
{
	for (FCatalogItem I : Result.Catalog)
	{
		if (I.CanBecomeCharacter) {
			UPlayFabCharacterItem* C = NewObject<UPlayFabCharacterItem>(this);
			C->ItemId = I.ItemId;
			C->DisplayName = I.DisplayName;
			C->ImageURI = I.ItemImageUrl;
			for (TPair<FString, uint32> P : I.VirtualCurrencyPrices) {
				if (P.Key == VirtualCurrency) {
					C->Price = P.Value;
					break;
				}
			}
			Characters.Add(C);
		}
	}
	// check owning status
	FListUsersCharactersRequest Request;
	Request.AuthenticationContext = GetLoginContextCpp();
	Request.PlayFabId = GetLoginPlayFabId();
	ClientAPI->GetAllUsersCharacters(Request,
		PlayFab::UPlayFabClientAPI::FGetAllUsersCharactersDelegate::CreateUObject(this, &APlayFabCharacterActor::OnGetPlayerCharactersSucess),
		DefaultErrorCpp);
}

void APlayFabCharacterActor::OnGetPlayerCharactersSucess(const FListUsersCharactersResult& Result)
{
	for (FCharacterResult R : Result.Characters) {
		for (UPlayFabCharacterItem* C : Characters)
		{
			if (C->ItemId == R.CharacterType)
			{
				C->bOwned = true;
				break;
			}
		}
	}
	OnGetCatalogCharacters.Broadcast();
}
