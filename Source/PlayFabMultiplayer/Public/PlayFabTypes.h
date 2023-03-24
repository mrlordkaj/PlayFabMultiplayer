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
	AustraliaEast = 0 UMETA(DisplayName = "AustraliaEast"),
	AustraliaSoutheast = 1 UMETA(DisplayName = "AustraliaSoutheast"),
	BrazilSouth = 2 UMETA(DisplayName = "BrazilSouth"),
	CentralUs = 3 UMETA(DisplayName = "CentralUs"),
	EastAsia = 4 UMETA(DisplayName = "EastAsia"),
	EastUs = 5 UMETA(DisplayName = "EastUs"),
	EastUs2 = 6 UMETA(DisplayName = "EastUs2"),
	JapanEast = 7 UMETA(DisplayName = "JapanEast"),
	JapanWest = 8 UMETA(DisplayName = "JapanWest"),
	NorthCentralUs = 9 UMETA(DisplayName = "NorthCentralUs"),
	NorthEurope = 10 UMETA(DisplayName = "NorthEurope"),
	SouthCentralUs = 11 UMETA(DisplayName = "SouthCentralUs"),
	SoutheastAsia = 12 UMETA(DisplayName = "SoutheastAsia"),
	WestEurope = 13 UMETA(DisplayName = "WestEurope"),
	WestUs = 14 UMETA(DisplayName = "WestUs"),
	SouthAfricaNorth = 15 UMETA(DisplayName = "SouthAfricaNorth"),
	WestCentralUs = 16 UMETA(DisplayName = "WestCentralUs"),
	KoreaCentral = 17 UMETA(DisplayName = "KoreaCentral"),
	FranceCentral = 18 UMETA(DisplayName = "FranceCentral"),
	WestUs2 = 19 UMETA(DisplayName = "WestUs2"),
	CentralIndia = 20 UMETA(DisplayName = "CentralIndia"),
	UaeNorth = 21 UMETA(DisplayName = "UaeNorth"),
	UkSouth = 22 UMETA(DisplayName = "UkSouth"),
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
