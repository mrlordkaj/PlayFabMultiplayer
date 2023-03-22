// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabBaseActor.h"
#include "PlayFabEnums.h"
#include "Core/PlayFabMultiplayerAPI.h"
#include "PlayFabMatchActor.generated.h"

using namespace PlayFab::MultiplayerModels;

/**
 * 
 */
UCLASS()
class PLAYFABMULTIPLAYER_API APlayFabMatchActor : public APlayFabBaseActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMatchFound, FString, Server, FString, Portal);

	APlayFabMatchActor();

public:
	virtual void BeginPlay() override;

protected:
	PlayFabMultiplayerPtr MultiplayerAPI;
	
	UPROPERTY(EditAnywhere, Category = "Matchmaking Settings")
	TMap<EAzureRegion, float> RegionLatencies;

	UPROPERTY(EditAnywhere, Category = "Matchmaking Settings", meta = (UIMin = "30", UIMax = "180", ClampMin = "30", ClampMax = "180"))
	int TicketTimeout = 60;

	UPROPERTY(EditAnywhere, Category = "Matchmaking Settings", meta = (UIMin = "7", UIMax = "10", ClampMin = "7", ClampMax = "10"))
	float RefreshTicketPeriod = 7;

	UPROPERTY(EditAnywhere, Category = "Matchmaking Settings")
	bool bAutoRenewTicket = true;

public:
	/* Broadcast event on match found. Message is connection address. */
	UPROPERTY(BlueprintAssignable)
	FMatchFound OnMatchFound;

	/* Broadcast event on ticket cancel. Message is the reason. */
	UPROPERTY(BlueprintAssignable)
	FGenericMessage OnTicketCancel;

	UPROPERTY(BlueprintReadOnly)
	FString TicketStatus;

	UPROPERTY(BlueprintReadWrite, Category = "Matchmaking Result")
	FString PawnClass;

	UPROPERTY(BlueprintReadOnly, Category = "Matchmaking Result")
	FString TargetMap;

	UFUNCTION(BlueprintCallable)
	void CreateTicket(FString QueueName, FString TargetMapName);

	UFUNCTION(BlueprintCallable)
	void CancelTicket();

private:
	/* The create matchmaking ticket request. */
	FCreateMatchmakingTicketRequest CreateTicketRequest;

	/* The get matchmaking ticket request. */
	FGetMatchmakingTicketRequest GetTicketRequest;

	/* Callback on create matchmaking ticket success. */
	void OnCreateTicketSuccess(const FCreateMatchmakingTicketResult& Result);

	/* Callback on get matchmaking ticket success. */
	void OnGetTicketSuccess(const FGetMatchmakingTicketResult& Result);

	/* Callback on get match success. */
	void OnGetMatchSuccess(const FGetMatchResult& Result);

	FTimerHandle RefreshTicketTimer;

	void RefreshTicket();
};
