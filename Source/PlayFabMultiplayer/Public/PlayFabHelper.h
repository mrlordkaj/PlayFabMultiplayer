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

	/* Gets authentication context stored in game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UPlayFabAuthenticationContext* GetLoginContext(UObject* WorldContextObject);

	/* Generates EntityKey for blueprint usage. */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"), DisplayName = "Get Login EntityKey")
	static UPlayFabJsonObject* GetLoginEntityKey(UObject* WorldContextObject);

	/* Checks current login status. */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static bool HasLogin(UObject* WorldContextObject);

	static void ReadVirtualCurrency(const PlayFab::ClientModels::FGetPlayerCombinedInfoResult& Result, FString Currency, int& Value);

	template<typename OutStructType>
	static void ReadUserData(const PlayFab::ClientModels::FGetPlayerCombinedInfoResult& Result, FString Key, OutStructType* OutStruct)
	{
		if (Result.InfoResultPayload->UserData.Contains(Key))
		{
			FUserDataRecord D = *Result.InfoResultPayload->UserData.Find(Key);
			FJsonObjectConverter::JsonObjectStringToUStruct(D.Value, OutStruct);
		}
	}
};



