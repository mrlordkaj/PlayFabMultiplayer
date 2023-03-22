// Copyright (C) 2022 Thinh Pham.


#include "PlayFabBaseComponent.h"
#include "PlayFabGameInstance.h"
#include "PlayFabMultiplayer.h"

UPlayFabBaseComponent::UPlayFabBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayFabBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// create common stuffs
	ClientAPI = IPlayFabModuleInterface::Get().GetClientAPI();
	DefaultErrorCpp = PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &UPlayFabBaseComponent::PlayFabErrorCpp);
}

FString UPlayFabBaseComponent::GetMyMasterId()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->PlayFabId;
}

FString UPlayFabBaseComponent::GetMyEntityId()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->EntityId;
}

UPlayFabJsonObject* UPlayFabBaseComponent::GetMyEntityKey()
{
	UPlayFabJsonObject* D = UPlayFabJsonObject::ConstructJsonObject(GetWorld());
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	if (!GI->EntityId.IsEmpty()) {
		D->SetStringField(TEXT("Id"), GI->EntityId);
		D->SetStringField(TEXT("Type"), TEXT("title_player_account"));
	}
	return D;
}

TSharedPtr<UPlayFabAuthenticationContext> UPlayFabBaseComponent::GetAuthenticationContextCpp()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->AuthenticationContext;
}

UPlayFabAuthenticationContext* UPlayFabBaseComponent::GetAuthenticationContext()
{
	return GetAuthenticationContextCpp().Get();
}

void UPlayFabBaseComponent::PlayFabErrorCpp(const PlayFab::FPlayFabCppError& Error)
{
	UE_LOG(LogPlayFabMultiplayer, Error, TEXT("%s"), *Error.GenerateErrorReport());
	OnPlayFabError.Broadcast(Error.ErrorName, Error.ErrorMessage, Error.ErrorCode);
}

void UPlayFabBaseComponent::PlayFapError(FPlayFabError Error, UObject* CustomData)
{
	UE_LOG(LogPlayFabMultiplayer, Error, TEXT("%s"), *Error.ErrorDetails);
	OnPlayFabError.Broadcast(Error.ErrorName, Error.ErrorMessage, Error.ErrorCode);
}

bool UPlayFabBaseComponent::HasLogin()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->AuthenticationContext.IsValid();
}
