// Copyright (C) 2022 Thinh Pham.


#include "MultiplayerUserComponent.h"
#include "PlayFabGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

UMultiplayerUserComponent::UMultiplayerUserComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 1;
	PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
	SetIsReplicatedByDefault(true);
}

void UMultiplayerUserComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	// check PlayFab link status
	if (!bPlayFabLinked && PlayFabId.Len() == 16)
	{
		bPlayFabLinked = true;
		EventPlayFabLinked();
		OnPlayFabLinked.Broadcast(PlayFabId);
	}
	// check team assign status
	if (!bTeamAssigned && !TeamId.IsEmpty())
	{
		bTeamAssigned = true;
		EventTeamAssigned();
		OnTeamAssigned.Broadcast(TeamId);
	}
	// disable tick to save resource
	if (bPlayFabLinked && bTeamAssigned) {
		SetComponentTickEnabled(false);
	}
}

UPlayFabAuthenticationContext* UMultiplayerUserComponent::GetPlayFabAuthContext()
{
	if (const UPlayFabGameInstance* GInst = GetWorld()->GetGameInstance<UPlayFabGameInstance>())
	{
		return GInst->PlayFabLoginContext;
	}
	return nullptr;
}

void UMultiplayerUserComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMultiplayerUserComponent, PlayFabId);
	DOREPLIFETIME(UMultiplayerUserComponent, TeamId);
}

void UMultiplayerUserComponent::EventPlayFabError_Implementation(FPlayFabError error, UObject* customData)
{
	FString Msg = FString::Printf(TEXT("PlayFabError: %s (%d)"), *error.ErrorMessage, error.ErrorCode);
	UKismetSystemLibrary::PrintString(GetWorld(), Msg, true, true, FLinearColor::Red);
	OnPlayFabError.Broadcast(Msg);
}
