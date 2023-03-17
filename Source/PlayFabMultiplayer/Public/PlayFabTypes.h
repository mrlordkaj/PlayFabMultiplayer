// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabTypes.generated.h"

/**
 * https://docs.microsoft.com/en-us/rest/api/playfab/multiplayer/multiplayer-server/list-multiplayer-servers?view=playfab-rest
 */
USTRUCT(BlueprintType)
struct FRegionLatency
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	FString Region;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	float Latency;
	
	FRegionLatency(FString RegionName = TEXT(""), float RegionLatency = 0)
	{
		Region = RegionName;
		Latency = RegionLatency;
	}
};

/**
 * https://docs.microsoft.com/en-us/rest/api/playfab/client/account-management/get-player-profile?view=playfab-rest#playerprofileviewconstraints
 */
USTRUCT(BlueprintType)
struct FPlayerProfileViewConstraints
{
	GENERATED_BODY()

	/* Whether to show player's avatar URL. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, SimpleDisplay)
	bool ShowAvatarUrl;

	/* Whether to show the banned until time. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowBannedUntil;

	/* Whether to show campaign attributions. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowCampaignAttributions;

	/* Whether to show contact email addresses. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowContactEmailAddresses;

	/* Whether to show the created date. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowCreated;

	/* Whether to show the display name. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, SimpleDisplay)
	bool ShowDisplayName;

	/* Whether to show player's experiment variants. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowExperimentVariants;

	/* Whether to show the last login time. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowLastLogin;

	/* Whether to show the linked accounts. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowLinkedAccounts;

	/* Whether to show player's locations. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowLocations;

	/* Whether to show player's membership information. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowMemberships;

	/* Whether to show origination. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowOrigination;

	/* Whether to show push notification registrations. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowPushNotificationRegistrations;

	/* Reserved for future development. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowStatistics;

	/* Whether to show tags. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowTags;

	/* Whether to show the total value to date in usd. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowTotalValueToDateInUsd;

	/* Whether to show the values to date. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowValuesToDate;
};
