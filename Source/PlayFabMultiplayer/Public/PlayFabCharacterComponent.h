// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabBaseComponent.h"
#include "PlayFabCharacterItem.h"
#include "PlayFabCharacterComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (PlayFab), meta = (BlueprintSpawnableComponent))
class PLAYFABMULTIPLAYER_API UPlayFabCharacterComponent : public UPlayFabBaseComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_DELEGATE(FPurchaseCharacterSuccess);

private:
	UPROPERTY(EditAnywhere)
	FString CatalogVersion = TEXT("Character");
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<UPlayFabCharacterItem*> Characters;

public:
	UPROPERTY(BlueprintAssignable)
	UPlayFabMultiplayer::FPlayFabGenericDelegate OnListCatalogCharactersSuccess;

	UFUNCTION(BlueprintCallable)
	void ListCatalogCharacters();

	UFUNCTION(BlueprintCallable)
	void PurchaseCharacter(FString ItemId, FString Currency, int Price, FString Name, FPurchaseCharacterSuccess OnSuccess);

private:
	FString PurchaseCharacterName;

	FPurchaseCharacterSuccess OnPurchaseCharacterSuccess;

	void ListCatalogCharactersSuccess(const PlayFab::ClientModels::FExecuteCloudScriptResult& Result);

	void PurchaseCharacterTokenSuccess(const PlayFab::ClientModels::FPurchaseItemResult& Result);

	void PurchaseCharacterSuccess(const PlayFab::ClientModels::FGrantCharacterToUserResult& Result);
};
