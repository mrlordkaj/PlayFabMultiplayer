// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayFabUserComponent.h"
#include "PlayFabGameInstance.h"
#include "PlayFabGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

UPlayFabUserComponent::UPlayFabUserComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UPlayFabUserComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AActor* Owner = GetOwner();
	UWorld* World = GetWorld();
	if (!Owner->HasAuthority() && UGameplayStatics::GetPlayerPawn(World, 0) == Owner) {
		UPlayFabGameInstance* GInst = Cast<UPlayFabGameInstance>(UGameplayStatics::GetGameInstance(World));
		if (GInst) {
			SubmitPlayerId(GInst->PlayerId);
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

//void UPlayFabUserComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//
//}

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
				FString::Printf(TEXT("LOCAL%d"), FMath::RandRange(10000, 99999));
		}
		GMode->RegisterPlayFabUser(PlayerId);
	}
}