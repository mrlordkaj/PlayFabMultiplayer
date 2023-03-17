// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabBaseActor.h"
#include "PlayFabTypes.h"
#include "PlayFabMatchActor.generated.h"

/**
 * 
 */
UCLASS()
class PLAYFABMULTIPLAYER_API APlayFabMatchActor : public APlayFabBaseActor
{
	GENERATED_BODY()

	APlayFabMatchActor();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Matchmaking Settings")
	TArray<FRegionLatency> RegionLatencies;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Matchmaking Settings")
	int TicketTimeout = 60;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FGenericDelegate OnMatchFound;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FGenericDelegate OnTicketCancel;

	UPROPERTY(BlueprintReadWrite, Category = "Matchmaking Result")
	FString ServerAddress;

	UPROPERTY(BlueprintReadWrite, Category = "Matchmaking Result")
	FString PawnClass;

	UPROPERTY(BlueprintReadWrite, Category = "Matchmaking Result")
	FString TeamId;

	UPROPERTY(BlueprintReadWrite, Category = "Matchmaking Result")
	FString TargetMap;
};
