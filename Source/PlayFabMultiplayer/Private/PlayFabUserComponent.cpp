// Copyright (C) 2022 Thinh Pham.


#include "PlayFabUserComponent.h"
#include "PlayFab.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

UPlayFabUserComponent::UPlayFabUserComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 1;
	PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
	SetIsReplicatedByDefault(true);
}

// void UPlayFabUserComponent::BeginPlay()
// {
// 	Super::BeginPlay();
//
// 	if (const APawn* Pawn = GetOwner<APawn>())
// 	{
// 		if (Pawn->IsLocallyControlled())
// 		{
// 			if (UPlayFabGameInstance* GInst = GetWorld()->GetGameInstance<UPlayFabGameInstance>())
// 			{
// 				SubmitPlayFabId(GInst->PlayFabId);
// 			}
// 		}
// 	}
// }

// void UPlayFabUserComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
// {
// 	Super::EndPlay(EndPlayReason);
//
// 	if (AMultiplayerGameMode* GMode = GetWorld()->GetAuthGameMode<AMultiplayerGameMode>())
// 	{
// 		GMode->UnregisterPlayFabUser(PlayerMasterId);
// 	}
// }

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

void UPlayFabUserComponent::OnPlayFabError(const PlayFab::FPlayFabCppError& ErrorResult) const
{
	FString Msg = FString::Printf(TEXT("%s (%d)"), *ErrorResult.ErrorMessage, ErrorResult.ErrorCode);
	UKismetSystemLibrary::PrintString(GetWorld(), Msg, true, true, FLinearColor::Red);
}

void UPlayFabUserComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPlayFabUserComponent, PlayFabId);
}

// void UPlayFabUserComponent::SubmitPlayFabId_Implementation(const FString& ClientPlayFabId)
// {
// 	PlayerMasterId = ClientPlayFabId;
// 	if (AMultiplayerGameMode* GMode = GetWorld()->GetAuthGameMode<AMultiplayerGameMode>())
// 	{
// 		if (PlayerMasterId.IsEmpty())
// 		{
// 			// apply abstract id for local testing
// 			int NumUsers = GMode->GetNumPlayFabUsers();
// 			PlayerMasterId = (NumUsers < DemoPlayFabUsers.Num())
// 							? PlayerMasterId = DemoPlayFabUsers[NumUsers]
// 							: FString::Printf(TEXT("LOCAL%d"), FMath::RandRange(100, 999));
// 		}
// 		GMode->RegisterPlayFabUser(PlayerMasterId);
// 	}
// }
