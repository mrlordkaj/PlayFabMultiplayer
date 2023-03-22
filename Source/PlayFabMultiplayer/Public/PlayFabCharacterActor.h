// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabCharacterItem.h"
#include "PlayFabBaseActor.h"
#include "PlayFabCharacterActor.generated.h"

using namespace PlayFab::ClientModels;

/**
 * 
 */
UCLASS(DisplayName = "PlayFab Character Actor")
class PLAYFABMULTIPLAYER_API APlayFabCharacterActor : public APlayFabBaseActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Catalog Settings")
	FString CatalogVersion = TEXT("Character");

	UPROPERTY(EditAnywhere, Category = "Catalog Settings")
	FString VirtualCurrency = TEXT("GD");

	UPROPERTY(BlueprintReadOnly)
	TArray<UPlayFabCharacterItem*> Characters;

public:
	UPROPERTY(BlueprintAssignable)
	FGenericDelegate OnGetCatalogCharacters;

	UFUNCTION(BlueprintCallable)
	void GetCatalogCharacters();

private:
	void OnGetCatalogCharactersSuccess(const FGetCatalogItemsResult& Result);

	void OnGetPlayerCharactersSucess(const FListUsersCharactersResult& Result);
};
