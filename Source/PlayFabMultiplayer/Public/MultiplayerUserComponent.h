// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabBaseModel.h"
#include "PlayFabClientAPI.h"
#include "PlayFabClientModels.h"
#include "PlayFabTypes.h"
#include "Components/ActorComponent.h"
#include "MultiplayerUserComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(PlayFabMultiplayer), meta=(BlueprintSpawnableComponent))
class PLAYFABMULTIPLAYER_API UMultiplayerUserComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMultiplayerUserComponent();

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTeamAssigned, FString, TeamId);
	/* Broadcast event when team assigned. */
	UPROPERTY(BlueprintAssignable, DisplayName="On Team Assigned")
	FOnTeamAssigned OnTeamAssigned;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayFabLinked, FString, PlayFabId);
	/* Broadcast event when PlayFab account is linked. */
	UPROPERTY(BlueprintAssignable, DisplayName="On PlayFab Linked")
	FOnPlayFabLinked OnPlayFabLinked;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayFabError, FString, Message);
	/* Broadcast event when PlayFab error threw message. */
	UPROPERTY(BlueprintAssignable, DisplayName="On PlayFab Error")
	FOnPlayFabError OnPlayFabError;

	/* Makes request struct for GetPlayerProfile function. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName="Make GetPlayerProfile Request")
	FClientGetPlayerProfileRequest MakeClientGetPlayerProfileRequest(FPlayerProfileViewConstraintsTest ViewConstrains);

protected:
	/* Internal event when PlayFab threw error message. */
	UFUNCTION(BlueprintCallable, DisplayName="PlayFap Error")
	void EventPlayFabError(FPlayFabError error, UObject* customData);

	/* Gets PlayFabAuthenticationContext stored in GameInstance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName="Get PlayFabContext")
	UPlayFabAuthenticationContext* GetPlayFabAuthContext();

private:
	UFUNCTION()
	void OnRep_PlayFabId();

	UFUNCTION()
	void OnRep_TeamId();

public:
	/* Replicated PlayFabId. */
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_PlayFabId, DisplayName = "PlayFabId")
	FString PlayFabId;

	/* Replicated TeamId. */
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_TeamId, DisplayName = "TeamId")
	FString TeamId;
};