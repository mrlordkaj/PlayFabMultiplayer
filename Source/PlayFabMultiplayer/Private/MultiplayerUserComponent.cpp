// Copyright (C) 2022 Thinh Pham.


#include "MultiplayerUserComponent.h"
#include "PlayFabMultiplayer.h"
#include "PlayFabGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

UMultiplayerUserComponent::UMultiplayerUserComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

FClientGetPlayerProfileRequest UMultiplayerUserComponent::MakeClientGetPlayerProfileRequest(FPlayerProfileViewConstraints ViewConstrains)
{
	FClientGetPlayerProfileRequest Request;
	Request.PlayFabId = PlayFabId;
	UPlayFabJsonObject* Json = Request.ProfileConstraints = UPlayFabJsonObject::ConstructJsonObject(GetWorld());
	if (ViewConstrains.ShowAvatarUrl) Json->SetBoolField("ShowAvatarUrl", true);
	if (ViewConstrains.ShowBannedUntil) Json->SetBoolField("ShowBannedUntil", true);
	if (ViewConstrains.ShowCampaignAttributions) Json->SetBoolField("ShowCampaignAttributions", true);
	if (ViewConstrains.ShowContactEmailAddresses) Json->SetBoolField("ShowContactEmailAddresses", true);
	if (ViewConstrains.ShowCreated) Json->SetBoolField("ShowCreated", true);
	if (ViewConstrains.ShowDisplayName) Json->SetBoolField("ShowDisplayName", true);
	if (ViewConstrains.ShowExperimentVariants) Json->SetBoolField("ShowExperimentVariants", true);
	if (ViewConstrains.ShowLastLogin) Json->SetBoolField("ShowLastLogin", true);
	if (ViewConstrains.ShowLinkedAccounts) Json->SetBoolField("ShowLinkedAccounts", true);
	if (ViewConstrains.ShowLocations) Json->SetBoolField("ShowLocations", true);
	if (ViewConstrains.ShowMemberships) Json->SetBoolField("ShowMemberships", true);
	if (ViewConstrains.ShowOrigination) Json->SetBoolField("ShowOrigination", true);
	if (ViewConstrains.ShowPushNotificationRegistrations) Json->SetBoolField("ShowPushNotificationRegistrations", true);
	if (ViewConstrains.ShowStatistics) Json->SetBoolField("ShowStatistics", true);
	if (ViewConstrains.ShowTags) Json->SetBoolField("ShowTags", true);
	if (ViewConstrains.ShowTotalValueToDateInUsd) Json->SetBoolField("ShowTotalValueToDateInUsd", true);
	if (ViewConstrains.ShowValuesToDate) Json->SetBoolField("ShowValuesToDate", true);
	Request.AuthenticationContext = GetPlayFabAuthContext();
	return Request;
}

UPlayFabAuthenticationContext* UMultiplayerUserComponent::GetPlayFabAuthContext()
{
	if (UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>())
	{
		return GI->PlayFabLogin.AuthenticationContext.Get();
	}
	return nullptr;
}

void UMultiplayerUserComponent::OnRep_PlayFabId()
{
	if (!GetOwner()->HasAuthority()) {
		if (PlayFabId.Len() == 16) {
			OnPlayFabLinked.Broadcast(PlayFabId);
		}
		else {
			UE_LOG(PlayFabMultiplayer, Warning, TEXT("PlayFabId %s is not valid."), *PlayFabId);
		}
	}
}

void UMultiplayerUserComponent::OnRep_TeamId()
{
	if (!GetOwner()->HasAuthority()) {
		OnTeamAssigned.Broadcast(TeamId);
	}
}

void UMultiplayerUserComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMultiplayerUserComponent, PlayFabId);
	DOREPLIFETIME(UMultiplayerUserComponent, TeamId);
}

void UMultiplayerUserComponent::EventPlayFabError(FPlayFabError error, UObject* customData)
{
	FString Msg = FString::Printf(TEXT("PlayFabError: %s (%d)"), *error.ErrorMessage, error.ErrorCode);
	UKismetSystemLibrary::PrintString(GetWorld(), Msg, true, true, FLinearColor::Red);
	OnPlayFabError.Broadcast(Msg);
}
