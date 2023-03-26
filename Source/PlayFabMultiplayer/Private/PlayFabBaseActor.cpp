// Copyright (C) 2022 Thinh Pham.


#include "PlayFabBaseActor.h"
#include "PlayFabGameInstance.h"
#include "PlayFabMultiplayer.h"

using namespace PlayFab::ClientModels;

APlayFabBaseActor::APlayFabBaseActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APlayFabBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
	// create common stuffs
	ClientAPI = IPlayFabModuleInterface::Get().GetClientAPI();
	DefaultErrorCpp = PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &APlayFabBaseActor::PlayFabErrorCpp);
}

FString APlayFabBaseActor::GetLoginEntityId()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->EntityId;
}

TSharedPtr<UPlayFabAuthenticationContext> APlayFabBaseActor::GetLoginContextCpp()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->AuthenticationContext;
}

FString APlayFabBaseActor::GetLoginPlayFabId()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->PlayFabId;
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
