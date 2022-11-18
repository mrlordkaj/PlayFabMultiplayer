// Copyright (C) 2022 Thinh Pham.


#include "MultiplayerHelper.h"
#include "MultiplayerUserComponent.h"

ETeamStatus UMultiplayerHelper::CheckTeamStatus(AActor* A, AActor* B)
{
	if (!A || !B) {
		return ETeamStatus::Invalid;
	}
	if (A == B) {
		return ETeamStatus::Self;
	}
	UActorComponent* ComA = A->GetComponentByClass(UMultiplayerUserComponent::StaticClass());
	UActorComponent* ComB = B->GetComponentByClass(UMultiplayerUserComponent::StaticClass());
	if (!ComA || !ComB) {
		return ETeamStatus::Neutral;
	}
	UMultiplayerUserComponent* UserA = Cast<UMultiplayerUserComponent>(ComA);
	UMultiplayerUserComponent* UserB = Cast<UMultiplayerUserComponent>(ComB);
	if (UserA->TeamId.IsEmpty() || UserB->TeamId.IsEmpty()) {
		return ETeamStatus::Neutral;
	}
	return (UserA->TeamId == UserB->TeamId) ? ETeamStatus::Ally : ETeamStatus::Enemy;
}
