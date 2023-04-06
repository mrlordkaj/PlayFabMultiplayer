// Copyright (C) 2022 Thinh Pham.


#include "PlayFabBaseActor.h"
#include "PlayFabGameInstance.h"
#include "PlayFabMultiplayer.h"

using namespace PlayFab::ClientModels;

APlayFabBaseActor::APlayFabBaseActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// create common stuffs
	ClientAPI = IPlayFabModuleInterface::Get().GetClientAPI();
	DefaultErrorCpp = PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &APlayFabBaseActor::PlayFabErrorCpp);
}

TSharedPtr<UPlayFabAuthenticationContext> APlayFabBaseActor::GetLoginContext()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->AuthenticationContext;
}

void APlayFabBaseActor::PlayFabErrorCpp(const PlayFab::FPlayFabCppError& Error)
{
	FPlayFabError E;
	E.ErrorCode = Error.ErrorCode;
	E.ErrorMessage = Error.ErrorMessage;
	E.ErrorName = Error.ErrorName;
	E.ErrorDetails = Error.GenerateErrorReport();
	PlayFapError(E, nullptr);
}

void APlayFabBaseActor::PlayFapError(FPlayFabError Error, UObject* CustomData)
{
	UE_LOG(LogPlayFabMultiplayer, Error, TEXT("%s"), *Error.ErrorDetails);
	OnPlayFabError.Broadcast(Error);
}
