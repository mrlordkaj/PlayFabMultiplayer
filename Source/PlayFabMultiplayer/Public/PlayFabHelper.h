// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Core/PlayFabClientAPI.h"
#include "JsonObjectConverter.h"
#include "PlayFabHelper.generated.h"

using namespace PlayFab::ClientModels;

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

	/* Gets authentication context stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UPlayFabAuthenticationContext* GetLoginContext(UObject* WorldContextObject);

	/* Generates EntityKey for blueprint usage. */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"), DisplayName = "Get Login EntityKey")
	static UPlayFabJsonObject* GetLoginEntityKey(UObject* WorldContextObject);

	/* Checks current login status. */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static bool HasLogin(UObject* WorldContextObject);

	static void ReadVirtualCurrency(const FGetPlayerCombinedInfoResult& Result, FString Currency, int& Value);

	static void ReadUserDataAsString(const TMap<FString, FUserDataRecord>& UserData, FString Key, FString& Value);

	static void ReadUserDataAsName(const TMap<FString, FUserDataRecord>& UserData, FString Key, FName& Name);

	template<typename OutStructType>
	static void ReadUserDataAsStruct(TMap<FString, FUserDataRecord> UserData, FString Key, OutStructType* OutStruct)
	{
		if (UserData.Contains(Key))
		{
			FUserDataRecord D = *UserData.Find(Key);
			FJsonObjectConverter::JsonObjectStringToUStruct(D.Value, OutStruct);
		}
	}

	template<typename InStructType>
	static FString EncodeJson(const InStructType& InStruct)
	{
		FString E;
		FJsonObjectConverter::UStructToJsonObjectString(InStructType::StaticStruct(), &InStruct, E, 0, 0, 0, nullptr, false);
		return E;
	}
};



