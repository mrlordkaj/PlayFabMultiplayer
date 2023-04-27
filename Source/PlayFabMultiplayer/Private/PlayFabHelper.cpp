// Copyright (C) 2022 Thinh Pham.


#include "PlayFabHelper.h"
#include "PlayFabGameInstance.h"

using namespace PlayFab::ClientModels;

bool UPlayFabHelper::IsValidUsername(FString Username)
{
	FRegexPattern P(TEXT("[\\w\\d]{4,64}"));
	FRegexMatcher M(P, Username);
	return M.FindNext();
}

bool UPlayFabHelper::IsValidEmail(FString Email)
{
	FRegexPattern P(TEXT("[\\w\\d\\-\\.]{2,}@[\\w\\d\\-\\.]{2,}\\.[\\w\\d\\-\\.]{2,}"));
	FRegexMatcher M(P, Email);
	return M.FindNext();
}

bool UPlayFabHelper::IsValidPassword(FString Password)
{
	return Password.Len() >= 6 && Password.Len() <= 100;
}

UPlayFabAuthenticationContext* UPlayFabHelper::GetLoginContext(UObject* WorldContextObject)
{
	UPlayFabGameInstance* GI = WorldContextObject->GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->AuthenticationContext.Get();
}

UPlayFabJsonObject* UPlayFabHelper::GetLoginEntityKey(UObject* WorldContextObject)
{
	UPlayFabJsonObject* D = UPlayFabJsonObject::ConstructJsonObject(WorldContextObject);
	UPlayFabGameInstance* GI = WorldContextObject->GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	if (!GI->EntityId.IsEmpty()) {
		D->SetStringField(TEXT("Id"), GI->EntityId);
		D->SetStringField(TEXT("Type"), TEXT("title_player_account"));
	}
	return D;
}

FString UPlayFabHelper::GetLoginPlayFabId(UObject* WorldContextObject)
{
	UPlayFabGameInstance* GI = WorldContextObject->GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->PlayFabId;
}

FString UPlayFabHelper::GetLoginEntityId(UObject* WorldContextObject)
{
	UPlayFabGameInstance* GI = WorldContextObject->GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->EntityId;
}

bool UPlayFabHelper::HasLogin(UObject* WorldContextObject)
{
	UPlayFabGameInstance* GI = WorldContextObject->GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->AuthenticationContext.IsValid();
}

int UPlayFabHelper::ReadItemPrice(const FCatalogItem& Item, FString Currency)
{
	return Item.VirtualCurrencyPrices.Contains(Currency) ?
		*Item.VirtualCurrencyPrices.Find(Currency) : 0;
}

int UPlayFabHelper::ReadVirtualCurrency(const FGetPlayerCombinedInfoResult& Result, FString Currency)
{
	return Result.InfoResultPayload->UserVirtualCurrency.Contains(Currency) ?
		*Result.InfoResultPayload->UserVirtualCurrency.Find(Currency) : 0;
}

FString UPlayFabHelper::ReadUserData(const TMap<FString, FUserDataRecord>& UserData, FString Key)
{
	if (UserData.Contains(Key))
	{
		FUserDataRecord D = *UserData.Find(Key);
		return D.Value;
	}
	return FString();
}
