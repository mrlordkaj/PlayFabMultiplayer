// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabBaseComponent.h"
#include "MultiplayerUserComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(PlayFabMultiplayer), meta=(BlueprintSpawnableComponent))
class PLAYFABMULTIPLAYER_API UMultiplayerUserComponent : public UPlayFabBaseComponent
{
	GENERATED_BODY()

protected:
	UMultiplayerUserComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:
	/* Broadcast event when team assigned. Message is the TeamId. */
	UPROPERTY(BlueprintAssignable)
	UPlayFabMultiplayer::FPlayFabGenericDelegate OnTeamAssigned;

	/* Broadcast event when PlayFab account is linked. Message is the PlayFabId. */
	UPROPERTY(BlueprintAssignable, DisplayName="On PlayFab Linked")
	UPlayFabMultiplayer::FPlayFabGenericDelegate OnPlayFabLinked;

protected:
	bool HasAuthority() { return GetOwner()->HasAuthority(); }

private:
	/* Previous values for change detection. */
	FString PrevPlayFabId, PrevTeamId;

public:
	/* Replicated PlayFabId. */
	UPROPERTY(BlueprintReadOnly, Replicated, DisplayName = "PlayFabId")
	FString PlayFabId;

	/* Replicated TeamId. */
	UPROPERTY(BlueprintReadWrite, Replicated, DisplayName = "TeamId")
	FString TeamId;
};