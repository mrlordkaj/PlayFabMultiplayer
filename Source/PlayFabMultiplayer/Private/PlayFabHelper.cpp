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
	FRegexPattern P(TEXT("[\\w\\d]{3,}@[\\w\\d]+\\.[\\w\\d]{2,}"));
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

bool UPlayFabHelper::HasLogin(UObject* WorldContextObject)
{
	UPlayFabGameInstance* GI = WorldContextObject->GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->AuthenticationContext.IsValid();
}

void UPlayFabHelper::ReadVirtualCurrency(const FGetPlayerCombinedInfoResult& Result, FString Currency, int& Value)
{
	if (Result.InfoResultPayload->UserVirtualCurrency.Contains(Currency))
	{
		Value = *Result.InfoResultPayload->UserVirtualCurrency.Find(Currency);
	}
}

void UPlayFabHelper::ReadUserDataString(const TMap<FString, FUserDataRecord>& UserData, FString Key, FString& Value)
{
	if (UserData.Contains(Key))
	{
		FUserDataRecord D = *UserData.Find(Key);
		Value = D.Value;
	}
}

void UPlayFabHelper::ReadUserDataAsName(const TMap<FString, FUserDataRecord>& UserData, FString Key, FName& Name)
{
	if (UserData.Contains(Key))
	{
		FUserDataRecord D = *UserData.Find(Key);
		Name = FName(D.Value);
	}
}
