// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabBaseModel.h"
#include "GameFramework/Actor.h"
#include "PlayFabBaseActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnErrorMessage, FString, Message);

UCLASS(DisplayName="PlayFab Base Actor")
class PLAYFABMULTIPLAYER_API APlayFabBaseActor : public AActor
{
	GENERATED_BODY()

public:
	APlayFabBaseActor();

	UPROPERTY(BlueprintAssignable)
	FOnErrorMessage OnErrorMessage;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, DisplayName="PlayFab Error")
	void PlayFapError(FPlayFabError Error, UObject* CustomData);
};
