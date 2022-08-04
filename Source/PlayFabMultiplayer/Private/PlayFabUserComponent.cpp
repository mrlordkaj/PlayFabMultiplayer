// Copyright (C) 2022 Thinh Pham.


#include "PlayFabUserComponent.h"
#include "PlayFabGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
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

	if (const APawn* Pawn = GetOwner<APawn>())
	{
		if (Pawn->IsLocallyControlled())
		{
			if (const UPlayFabGameInstance* GInst = GetWorld()->GetGameInstance<UPlayFabGameInstance>())
			{
				LoginContext = GInst->PlayFabLoginContext;
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s can be holded by pawn only."), *GetClass()->GetName())
	}
}

void UPlayFabUserComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	if (!bPlayFabLinked && PlayFabId.Len() == 16)
	{
		EventPlayFabLinked();
		OnPlayFabLinked.Broadcast(PlayFabId);
		bPlayFabLinked = true;
	}

	if (!bTeamAssiged && !TeamId.IsEmpty())
	{
		EventTeamAssigned();
		OnTeamAssigned.Broadcast(TeamId);
		bTeamAssiged = true;
	}
	
	// if (!PlayFabId.IsEmpty())
	// {
	// 	if (PlayFabId.Len() == 16)
	// 	{
	// 		OnPlayFabIdReceived();
	//
	// 		// PlayFab::ClientModels::FGetPlayerProfileRequest Request;
	// 		// // TODO: Request.AuthenticationContext
	// 		// Request.PlayFabId = PlayFabId;
	// 		//
	// 		// PlayFabClientPtr ClientAPI = IPlayFabModuleInterface::Get().GetClientAPI();
	// 		// ClientAPI->GetPlayerProfile(Request,
	// 		//                             PlayFab::UPlayFabClientAPI::FGetPlayerProfileDelegate::CreateUObject(
	// 		// 	                            this, &UPlayFabUserComponent::OnGetPlayerProfileSuccess),
	// 		//                             PlayFab::FPlayFabErrorDelegate::CreateUObject(
	// 		// 	                            this, &UPlayFabUserComponent::OnPlayFabError)
	// 		// );
	// 	}
	// 	SetComponentTickEnabled(false);
	// }
}

// void UPlayFabUserComponent::OnGetPlayerProfileSuccess(const PlayFab::ClientModels::FGetPlayerProfileResult& Result)
// {
// 	DisplayName = Result.PlayerProfile->DisplayName;
// }
//
// void UPlayFabUserComponent::OnPlayFabError(const PlayFab::FPlayFabCppError& ErrorResult) const
// {
// 	FString Msg = FString::Printf(TEXT("%s (%d)"), *ErrorResult.ErrorMessage, ErrorResult.ErrorCode);
// 	UKismetSystemLibrary::PrintString(GetWorld(), Msg, true, true, FLinearColor::Red);
// }

void UPlayFabUserComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPlayFabUserComponent, PlayFabId);
	DOREPLIFETIME(UPlayFabUserComponent, TeamId);
}

void UPlayFabUserComponent::EventPlayFabError_Implementation(FPlayFabError Error, UObject* CustomData)
{
	FString Msg = FString::Printf(TEXT("PlayFabError: %s (%d)"), *Error.ErrorMessage, Error.ErrorCode);
	UKismetSystemLibrary::PrintString(GetWorld(), Msg, true, true, FLinearColor::Red);
}
