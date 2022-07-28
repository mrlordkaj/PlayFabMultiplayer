// Copyright (C) 2022 Thinh Pham.


#include "PlayFabUserComponent.h"
#include "PlayFabGameInstance.h"
#include "PlayFabGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PlayFab.h"
#include "Net/UnrealNetwork.h"

UPlayFabUserComponent::UPlayFabUserComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 1;
	PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
	SetIsReplicatedByDefault(true);
}

void UPlayFabUserComponent::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	AActor* Owner = GetOwner();
	if (!Owner->HasAuthority() && UGameplayStatics::GetPlayerPawn(World, 0) == Owner)
	{
		UPlayFabGameInstance* GInst = Cast<UPlayFabGameInstance>(UGameplayStatics::GetGameInstance(World));
		if (GInst)
		{
			SubmitPlayFabId(GInst->PlayFabId);
		}
	}
}

void UPlayFabUserComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	APlayFabGameMode* GMode = Cast<APlayFabGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GMode && GMode->HasAuthority())
	{
		GMode->UnregisterPlayFabUser(PlayFabId);
	}
}

void UPlayFabUserComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	if (!PlayFabId.IsEmpty())
	{
		if (PlayFabId.Len() == 16)
		{
			PlayFab::ClientModels::FGetPlayerProfileRequest Request;
			// TODO: Request.AuthenticationContext
			Request.PlayFabId = PlayFabId;

			PlayFabClientPtr ClientAPI = IPlayFabModuleInterface::Get().GetClientAPI();
			ClientAPI->GetPlayerProfile(Request,
			                            PlayFab::UPlayFabClientAPI::FGetPlayerProfileDelegate::CreateUObject(
				                            this, &UPlayFabUserComponent::OnGetPlayerProfileSuccess),
			                            PlayFab::FPlayFabErrorDelegate::CreateUObject(
				                            this, &UPlayFabUserComponent::OnPlayFabError)
			);
		}
		SetComponentTickEnabled(false);
	}
}

void UPlayFabUserComponent::OnGetPlayerProfileSuccess(const PlayFab::ClientModels::FGetPlayerProfileResult& Result)
{
	DisplayName = Result.PlayerProfile->DisplayName;
}

void UPlayFabUserComponent::OnPlayFabError(const PlayFab::FPlayFabCppError& ErrorResult)
{
	FString Msg = FString::Printf(TEXT("%s (%d)"), *ErrorResult.ErrorMessage, ErrorResult.ErrorCode);
	UKismetSystemLibrary::PrintString(GetWorld(), Msg, true, true, FLinearColor::Red);
}

void UPlayFabUserComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPlayFabUserComponent, PlayFabId);
}

void UPlayFabUserComponent::SubmitPlayFabId_Implementation(const FString& ClientPlayFabId)
{
	PlayFabId = ClientPlayFabId;
	APlayFabGameMode* GMode = Cast<APlayFabGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GMode)
	{
		if (PlayFabId.IsEmpty())
		{
			// apply abstract id for local testing
			int NumUsers = GMode->GetNumPlayFabUsers();
			PlayFabId = (NumUsers < DemoPlayFabUsers.Num())
				            ? PlayFabId = DemoPlayFabUsers[NumUsers]
				            : FString::Printf(TEXT("LOCAL%d"), FMath::RandRange(100, 999));
		}
		GMode->RegisterPlayFabUser(PlayFabId);
	}
}
