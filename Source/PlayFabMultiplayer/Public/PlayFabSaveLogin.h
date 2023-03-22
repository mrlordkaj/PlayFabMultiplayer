// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayFabSaveLogin.generated.h"

/**
 * 
 */
UCLASS()
class PLAYFABMULTIPLAYER_API UPlayFabSaveLogin : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	EPlayFabLoginMethod Method;

	UPROPERTY()
	FString Identity;

	UPROPERTY()
	FString Token;
};
