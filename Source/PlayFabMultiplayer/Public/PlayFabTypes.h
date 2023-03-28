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
	Unavailable,
};

USTRUCT(BlueprintType)
struct FPlayFabLatency
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayFabRegion Region = EPlayFabRegion::Unavailable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Latency = 0;
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
	bool ShowAvatarUrl = false;

	/* Whether to show the banned until time. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowBannedUntil = false;

	/* Whether to show campaign attributions. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowCampaignAttributions = false;

	/* Whether to show contact email addresses. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowContactEmailAddresses = false;

	/* Whether to show the created date. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowCreated = false;

	/* Whether to show the display name. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, SimpleDisplay)
	bool ShowDisplayName = false;

	/* Whether to show player's experiment variants. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowExperimentVariants = false;

	/* Whether to show the last login time. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowLastLogin = false;

	/* Whether to show the linked accounts. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowLinkedAccounts = false;

	/* Whether to show player's locations. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowLocations = false;

	/* Whether to show player's membership information. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowMemberships = false;

	/* Whether to show origination. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowOrigination = false;

	/* Whether to show push notification registrations. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowPushNotificationRegistrations = false;

	/* Reserved for future development. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowStatistics = false;

	/* Whether to show tags. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowTags = false;

	/* Whether to show the total value to date in usd. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowTotalValueToDateInUsd = false;

	/* Whether to show the values to date. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, AdvancedDisplay)
	bool ShowValuesToDate = false;
};
