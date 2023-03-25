// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Core/PlayFabClientAPI.h"
#include "PlayFabHelper.generated.h"

/**
 * 
 */
UCLASS()
class PLAYFABMULTIPLAYER_API UPlayFabHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool IsValidUsername(FString Username);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool IsValidEmail(FString Email);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool IsValidPassword(FString Password);
};

static void ReadVirtualCurrency(const PlayFab::ClientModels::FGetPlayerCombinedInfoResult& Result, FString Currency, int& Value)
{
	if (Result.InfoResultPayload->UserVirtualCurrency.Contains(Currency))
	{
		Value = *Result.InfoResultPayload->UserVirtualCurrency.Find(Currency);
	}
}

template<typename OutStructType>
static void ReadUserData(const PlayFab::ClientModels::FGetPlayerCombinedInfoResult& Result, FString Key, OutStructType* OutStruct)
{
	if (Result.InfoResultPayload->UserData.Contains(Key))
	{
		FUserDataRecord D = *Result.InfoResultPayload->UserData.Find(Key);
		FJsonObjectConverter::JsonObjectStringToUStruct(D.Value, OutStruct);
	}
}