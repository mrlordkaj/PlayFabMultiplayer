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

FString UPlayFabBaseComponent::GetLoginPlayFabId()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->PlayFabId;
}

FString UPlayFabBaseComponent::GetLoginEntityId()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->EntityId;
}

UPlayFabJsonObject* UPlayFabBaseComponent::GetLoginEntityKey()
{
	UWorld* W = GetWorld();
	UPlayFabJsonObject* D = UPlayFabJsonObject::ConstructJsonObject(W);
	UPlayFabGameInstance* GI = W->GetGameInstance<UPlayFabGameInstance>();
	if (!GI->EntityId.IsEmpty()) {
		D->SetStringField(TEXT("Id"), GI->EntityId);
		D->SetStringField(TEXT("Type"), TEXT("title_player_account"));
	}
	return D;
}

TSharedPtr<UPlayFabAuthenticationContext> UPlayFabBaseComponent::GetLoginContextCpp()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->AuthenticationContext;
}

UPlayFabAuthenticationContext* UPlayFabBaseComponent::GetLoginContext()
{
	return GetLoginContextCpp().Get();
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
