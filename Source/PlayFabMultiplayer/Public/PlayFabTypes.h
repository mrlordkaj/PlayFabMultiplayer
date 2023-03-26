// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabTypes.generated.h"

UENUM(BlueprintType, DisplayName = "PlayFab Login Method")
enum class EPlayFabLoginMethod : uint8
{
	PlayFab,
	EmailAddress,
	Facebook
};

/**
 * AzureRegion
 */
UENUM(BlueprintType)
enum class EPlayFabRegion : uint8
{
	AustraliaEast UMETA(DisplayName = "AustraliaEast"),
	AustraliaSoutheast UMETA(DisplayName = "AustraliaSoutheast"),
	BrazilSouth UMETA(DisplayName = "BrazilSouth"),
	CentralUs UMETA(DisplayName = "CentralUs"),
	EastAsia UMETA(DisplayName = "EastAsia"),
	EastUs UMETA(DisplayName = "EastUs"),
	EastUs2 UMETA(DisplayName = "EastUs2"),
	JapanEast UMETA(DisplayName = "JapanEast"),
	JapanWest UMETA(DisplayName = "JapanWest"),
	NorthCentralUs UMETA(DisplayName = "NorthCentralUs"),
	NorthEurope UMETA(DisplayName = "NorthEurope"),
	SouthCentralUs UMETA(DisplayName = "SouthCentralUs"),
	SoutheastAsia UMETA(DisplayName = "SoutheastAsia"),
	WestEurope UMETA(DisplayName = "WestEurope"),
	WestUs UMETA(DisplayName = "WestUs"),
	SouthAfricaNorth UMETA(DisplayName = "SouthAfricaNorth"),
	WestCentralUs UMETA(DisplayName = "WestCentralUs"),
	KoreaCentral UMETA(DisplayName = "KoreaCentral"),
	FranceCentral UMETA(DisplayName = "FranceCentral"),
	WestUs2 UMETA(DisplayName = "WestUs2"),
	CentralIndia UMETA(DisplayName = "CentralIndia"),
	UaeNorth UMETA(DisplayName = "UaeNorth"),
	UkSouth UMETA(DisplayName = "UkSouth"),
};

USTRUCT(BlueprintType)
struct FPlayFabLatency
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayFabRegion Region;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Latency;
};

USTRUCT(BlueprintType)
struct FPlayFabUserAttributes
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPlayFabLatency> Latencies;

	UPROPERTY(BlueprintReadWrite)
	FString DisplayName;

	UPROPERTY(BlueprintReadWrite)
	FString AvatarUrl;
};

/**
 * https://docs.microsoft.com/en-us/rest/api/playfab/client/account-management/get-player-profile?view=playfab-rest#playerprofileviewconstraints
 */
USTRUCT(BlueprintType)
struct FPlayerProfileViewConstraintsTest
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
