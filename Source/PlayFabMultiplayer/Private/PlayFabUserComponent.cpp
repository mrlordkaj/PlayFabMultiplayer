// Copyright (C) 2022 Thinh Pham.


#include "PlayFabUserComponent.h"
#include "PlayFabGameInstance.h"
#include "PlayFabGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PlayFab.h"

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

	GInst = Cast<UPlayFabGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	AActor* Owner = GetOwner();
	if (!Owner->HasAuthority() && UGameplayStatics::GetPlayerPawn(GetWorld(), 0) == Owner) {
		if (GInst) {
			SubmitPlayerId(GInst->PlayFabMasterId);
		}
	}
}

void UPlayFabUserComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	APlayFabGameMode* GMode = Cast<APlayFabGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GMode && GMode->HasAuthority()) {
		GMode->UnregisterPlayFabUser(PlayerId);
	}
}

void UPlayFabUserComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (!PlayerId.IsEmpty()) {
		if (PlayerId.Len() == 16) {
			PlayFab::ClientModels::FGetPlayerProfileRequest Request;
			// TODO: Request.AuthenticationContext
			Request.PlayFabId = PlayerId;

			PlayFabClientPtr ClientAPI = IPlayFabModuleInterface::Get().GetClientAPI();
			ClientAPI->GetPlayerProfile(Request,
				PlayFab::UPlayFabClientAPI::FGetPlayerProfileDelegate::CreateUObject(this, &UPlayFabUserComponent::OnGetPlayerProfileSuccess),
				PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &UPlayFabUserComponent::OnPlayFabError)
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
	DisplayName = TEXT("Error");
}

void UPlayFabUserComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPlayFabUserComponent, PlayerId);
}

void UPlayFabUserComponent::SubmitPlayerId_Implementation(const FString& ClientPlayerId)
{
	PlayerId = ClientPlayerId;
	APlayFabGameMode* GMode = Cast<APlayFabGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GMode) {
		if (PlayerId.IsEmpty()) {
			// apply abstract id for local testing
			int NumUsers = GMode->GetNumPlayFabUsers();
			PlayerId = (NumUsers < DemoPlayFabUsers.Num()) ?
				PlayerId = DemoPlayFabUsers[NumUsers] :
				FString::Printf(TEXT("LOCAL%d"), FMath::RandRange(100, 999));
		}
		GMode->RegisterPlayFabUser(PlayerId);
	}
}