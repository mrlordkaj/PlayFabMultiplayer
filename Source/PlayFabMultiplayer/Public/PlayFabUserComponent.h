// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabBaseModel.h"
#include "Components/ActorComponent.h"
#include "Core/PlayFabClientAPI.h"
#include "PlayFabUserComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(PlayFabMultiplayer), meta=(BlueprintSpawnableComponent))
class PLAYFABMULTIPLAYER_API UPlayFabUserComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayFabUserComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTeamAssigned, FString, TeamId);

	UPROPERTY(BlueprintAssignable)
	FOnTeamAssigned OnTeamAssigned;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayFabLinked, FString, PlayFabId);

	UPROPERTY(BlueprintAssignable, DisplayName="On PlayFab Linked")
	FOnPlayFabLinked OnPlayFabLinked;

protected:
	/* Internal event when PlayFab is linked. */
	UFUNCTION(BlueprintImplementableEvent, DisplayName="PlayFab Linked")
	void EventPlayFabLinked();

	/* Internal event when team asssigned. */
	UFUNCTION(BlueprintImplementableEvent, DisplayName="Team Assigned")
	void EventTeamAssigned();

private:
	/* Flag for team assignation status. */
	bool bTeamAssiged = false;

	/* Flag for PlayFab linking status. */
	bool bPlayFabLinked = false;

protected:
	/* FlayFab Authentication Context. */
	UPROPERTY(BlueprintReadOnly)
	UPlayFabAuthenticationContext* LoginContext;

public:
	UPROPERTY(BlueprintReadOnly, Replicated)
	FString PlayFabId;

	UPROPERTY(BlueprintReadOnly, Replicated)
	FString TeamId;

	// /* Player display name inside title. */
	// UPROPERTY(BlueprintReadOnly)
	// FString DisplayName;

// private:
// 	void OnGetPlayerProfileSuccess(const PlayFab::ClientModels::FGetPlayerProfileResult& Result);
// 	void OnPlayFabError(const PlayFab::FPlayFabCppError& ErrorResult) const;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, DisplayName="PlayFap Error")
	void EventPlayFabError(FPlayFabError Error, UObject* CustomData);
};
