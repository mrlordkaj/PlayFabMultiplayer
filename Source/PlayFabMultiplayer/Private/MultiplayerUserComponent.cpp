// Copyright (C) 2022 Thinh Pham.


#include "MultiplayerUserComponent.h"
#include "PlayFabMultiplayer.h"
#include "Net/UnrealNetwork.h"

UMultiplayerUserComponent::UMultiplayerUserComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.5f;
	SetIsReplicatedByDefault(true);
}

void UMultiplayerUserComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMultiplayerUserComponent, PlayFabId);
	DOREPLIFETIME(UMultiplayerUserComponent, TeamId);
}

void UMultiplayerUserComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayFabId != PrevPlayFabId)
	{
		if (PlayFabId.Len() == 16) {
			OnPlayFabLinked.Broadcast();
		}
		else {
			UE_LOG(LogPlayFabMultiplayer, Warning, TEXT("Invalid PlayFabId %s."), *PlayFabId);
		}
		PrevPlayFabId = PlayFabId;
	}
	if (TeamId != PrevTeamId)
	{
		OnTeamAssigned.Broadcast();
		PrevTeamId = TeamId;
	}
}
