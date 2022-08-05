// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabBaseModel.h"
#include "PlayFabClientAPI.h"
#include "Components/ActorComponent.h"
#include "MultiplayerUserComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(PlayFabMultiplayer), meta=(BlueprintSpawnableComponent))
class PLAYFABMULTIPLAYER_API UMultiplayerUserComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMultiplayerUserComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
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

protected:
	/* Internal event when PlayFab account is linked to the pawn. */
	UFUNCTION(BlueprintImplementableEvent, DisplayName="PlayFab Linked")
	void EventPlayFabLinked();

	/* Internal event when player be assigned to a team. */
	UFUNCTION(BlueprintImplementableEvent, DisplayName="Team Assigned")
	void EventTeamAssigned();

	/* Internal event when PlayFab threw error message. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, DisplayName="PlayFap Error")
	void EventPlayFabError(FPlayFabError error, UObject* customData);

	/* Get PlayFabAuthenticationContext stored in GameInstance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName="Get PlayFabContext")
	UPlayFabAuthenticationContext* GetPlayFabAuthContext();

private:
	/* Flag for team assignation status. */
	bool bTeamAssigned = false;

	/* Flag for PlayFab linking status. */
	bool bPlayFabLinked = false;

public:
	UPROPERTY(BlueprintReadOnly, Replicated, DisplayName="PlayFabId")
	FString PlayFabId;

	UPROPERTY(BlueprintReadOnly, Replicated, DisplayName="TeamId")
	FString TeamId;
};