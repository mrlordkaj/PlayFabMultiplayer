// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayFabUserComponent.generated.h"


UCLASS( Blueprintable, ClassGroup=(PlayFabMultiplayer), meta=(BlueprintSpawnableComponent) )
class PLAYFABMULTIPLAYER_API UPlayFabUserComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayFabUserComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

//public:
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/* PlayerID used in title only. */
	UPROPERTY(BlueprintReadOnly, Replicated)
	FString PlayerId;

private:
	/* Use to send target map to server lobby. */
	UFUNCTION(Server, Unreliable)
	virtual void SubmitPlayerId(const FString& ClientPlayerId);

protected:
	/* List samples of PlayerId for testing on local. */
	UPROPERTY(EditDefaultsOnly, Category = "Debugging")
	TArray<FString> DemoPlayFabUsers;
};
