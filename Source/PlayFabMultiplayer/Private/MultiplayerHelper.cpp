// Copyright (C) 2022 Thinh Pham.


#include "MultiplayerHelper.h"
#include "MultiplayerUserComponent.h"

ETeamStatus UMultiplayerHelper::CheckTeamStatus(AActor* A, AActor* B)
{
	if (!A || !B) {
		return ETeamStatus::Invalid;
	}
	if (A == B) {
		return ETeamStatus::Itself;
	}
	UActorComponent* ComA = A->GetComponentByClass(UMultiplayerUserComponent::StaticClass());
	UActorComponent* ComB = B->GetComponentByClass(UMultiplayerUserComponent::StaticClass());
	if (!ComA || !ComB) {
		return ETeamStatus::Invalid;
	}
	FString TeamA = Cast<UMultiplayerUserComponent>(ComA)->TeamId;
	FString TeamB = Cast<UMultiplayerUserComponent>(ComB)->TeamId;
	if (TeamA.IsEmpty() || TeamB.IsEmpty()) {
		return ETeamStatus::Neutral;
	}
	return (TeamA == TeamB) ? ETeamStatus::Ally : ETeamStatus::Enemy;
}
