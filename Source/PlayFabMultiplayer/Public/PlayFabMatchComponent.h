// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "Core/PlayFabMultiplayerAPI.h"
#include "PlayFabTypes.h"
#include "PlayFabEnums.h"
#include "PlayFabBaseComponent.h"
#include "PlayFabMatchPlayerEntry.h"
#include "PlayFabMatchComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (PlayFab), meta = (BlueprintSpawnableComponent))
class PLAYFABMULTIPLAYER_API UPlayFabMatchComponent : public UPlayFabBaseComponent
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDelegateMatchFound, FString, Server, FString, Portal, const TArray<UPlayFabMatchPlayerEntry*>&, Players);

public:
	virtual void BeginPlay() override;

protected:
	PlayFabMultiplayerPtr MultiplayerAPI;

	UPROPERTY(EditAnywhere, Category = "Matchmaking Settings", meta = (UIMin = "60", UIMax = "300", ClampMin = "60", ClampMax = "300"))
	int TicketTimeout = 120;

	UPROPERTY(EditAnywhere, Category = "Matchmaking Settings", meta = (UIMin = "7", UIMax = "10", ClampMin = "7", ClampMax = "10"))
	float RefreshTicketPeriod = 7;

	UPROPERTY(EditAnywhere, Category = "Matchmaking Settings")
	bool bAutoRenewTicket = true;

public:
	/* Broadcast event on match found. */
	UPROPERTY(BlueprintAssignable)
	FDelegateMatchFound OnMatchFound;

	UPROPERTY(BlueprintAssignable)
	UPlayFabMultiplayer::FPlayFabGenericDelegate OnTicketCreated;

	/* Broadcast event on ticket cancel. Message is the reason. */
	UPROPERTY(BlueprintAssignable)
	UPlayFabMultiplayer::FPlayFabMessageDelegate OnTicketCanceled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Matchmaking Settings")
	FPlayFabUserAttributes UserAttributes;

	UPROPERTY(BlueprintReadWrite)
	FString PawnClass;

	UFUNCTION(BlueprintCallable)
	void CreateTicket(FString QueueName, bool bCancelPreviously = true);

	UFUNCTION(BlueprintCallable)
	void CancelTicket();

private:
	//int AverageQueueTime;

	/* Refreshs matchmaking ticket status. */
	void RefreshTicket();

	/* The create matchmaking ticket request. */
	PlayFab::MultiplayerModels::FCreateMatchmakingTicketRequest CreateTicketRequest;

	/* The get matchmaking ticket request. */
	PlayFab::MultiplayerModels::FGetMatchmakingTicketRequest GetTicketRequest;

	/* Timer for refresh ticket status. */
	FTimerHandle RefreshTicketTimer;

	///* Callback on create matchmaking ticket success. */
	//void GetQueueStatisticsSuccess(const PlayFab::MultiplayerModels::FGetQueueStatisticsResult& Result);

	void CancelAllTicketsSuccess(const PlayFab::MultiplayerModels::FCancelAllMatchmakingTicketsForPlayerResult& Result);

	/* Callback on create matchmaking ticket success. */
	void CreateTicketSuccess(const PlayFab::MultiplayerModels::FCreateMatchmakingTicketResult& Result);

	/* Callback on get matchmaking ticket success. */
	void GetTicketSuccess(const PlayFab::MultiplayerModels::FGetMatchmakingTicketResult& Result);

	/* Callback on cancel matchmaking ticket success. */
	void CancelTicketSuccess(const PlayFab::MultiplayerModels::FCancelMatchmakingTicketResult& Result);

	/* Callback on get match success. */
	void GetMatchSuccess(const PlayFab::MultiplayerModels::FGetMatchResult& Result);
};
