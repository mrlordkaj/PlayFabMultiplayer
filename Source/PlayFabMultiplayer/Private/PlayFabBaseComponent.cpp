// Copyright (C) 2022 Thinh Pham.


#include "PlayFabBaseComponent.h"
#include "PlayFabGameInstance.h"
#include "PlayFabMultiplayer.h"

UPlayFabBaseComponent::UPlayFabBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// create common stuffs
	ClientAPI = IPlayFabModuleInterface::Get().GetClientAPI();
	DefaultErrorCpp = PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &UPlayFabBaseComponent::PlayFabErrorCpp);
}

TSharedPtr<UPlayFabAuthenticationContext> UPlayFabBaseComponent::GetLoginContext()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->AuthenticationContext;
}

void UPlayFabBaseComponent::PlayFabErrorCpp(const PlayFab::FPlayFabCppError& Error)
{
	FPlayFabError E;
	E.ErrorCode = Error.ErrorCode;
	E.ErrorMessage = Error.ErrorMessage;
	E.ErrorName = Error.ErrorName;
	E.ErrorDetails = Error.GenerateErrorReport();
	PlayFapError(E, nullptr);
}

void UPlayFabBaseComponent::PlayFapError(FPlayFabError Error, UObject* CustomData)
{
	UE_LOG(LogPlayFabMultiplayer, Error, TEXT("%s"), *Error.ErrorDetails);
	OnPlayFabError.Broadcast(Error);
}
