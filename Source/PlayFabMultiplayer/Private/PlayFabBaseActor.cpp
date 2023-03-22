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
	// create client api
	ClientAPI = IPlayFabModuleInterface::Get().GetClientAPI();
	// create default error delegate
	DefaultErrorDelegate = PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &APlayFabBaseActor::PlayFabErrorCpp);
}

FString APlayFabBaseActor::GetEntityId()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->EntityId;
}

UPlayFabJsonObject* APlayFabBaseActor::GetEntityKey()
{
	UPlayFabJsonObject* D = UPlayFabJsonObject::ConstructJsonObject(GetWorld());
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	if (!GI->EntityId.IsEmpty()) {
		D->SetStringField(TEXT("Id"), GI->EntityId);
		D->SetStringField(TEXT("Type"), TEXT("title_player_account"));
	}
	return D;
}

TSharedPtr<UPlayFabAuthenticationContext> APlayFabBaseActor::GetAuthenticationContextCpp()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->AuthenticationContext;
}

UPlayFabAuthenticationContext* APlayFabBaseActor::GetAuthenticationContext()
{
	return GetAuthenticationContextCpp().Get();
}

FString APlayFabBaseActor::GetPlayFabId()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->PlayFabId;
}

void APlayFabBaseActor::PlayFabErrorCpp(const PlayFab::FPlayFabCppError& Error)
{
	UE_LOG(LogPlayFabMultiplayer, Error, TEXT("%s"), *Error.GenerateErrorReport());
	OnPlayFabError.Broadcast(Error.ErrorName, Error.ErrorMessage, Error.ErrorCode);
}

void APlayFabBaseActor::PlayFapError(FPlayFabError Error, UObject* CustomData)
{
	UE_LOG(LogPlayFabMultiplayer, Error, TEXT("%s"), *Error.ErrorDetails);
	OnPlayFabError.Broadcast(Error.ErrorName, Error.ErrorMessage, Error.ErrorCode);
}

bool APlayFabBaseActor::HasLogin()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GI->AuthenticationContext.IsValid();
}

