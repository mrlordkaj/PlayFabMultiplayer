// Copyright (C) 2022 Thinh Pham.


#include "PlayFabBaseActor.h"
#include "PlayFab.h"
#include "PlayFabGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

using namespace PlayFab::ClientModels;

APlayFabBaseActor::APlayFabBaseActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APlayFabBaseActor::BeginPlay()
{
	Super::BeginPlay();

	ClientAPI = IPlayFabModuleInterface::Get().GetClientAPI();
}

FLoginResult APlayFabBaseActor::GetLoginResult()
{
	if (UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>())
	{
		return GI->PlayFabLogin;
	}
	return FLoginResult();
}

void APlayFabBaseActor::PlayFapError(FPlayFabError Error, UObject* CustomData)
{
	FString Msg = FString::Printf(TEXT("PlayFabError: %s (%d)"), *Error.ErrorMessage, Error.ErrorCode);
	UKismetSystemLibrary::PrintString(GetWorld(), Msg, true, true, FLinearColor::Red);
	OnErrorMessage.Broadcast(Msg);
}

UPlayFabAuthenticationContext* APlayFabBaseActor::GetLoginContext()
{
	return GetLoginResult().AuthenticationContext.Get();
}

UPlayFabJsonObject* APlayFabBaseActor::GetPlayFabEntity()
{
	UPlayFabJsonObject* D = UPlayFabJsonObject::ConstructJsonObject(GetWorld());
	FLoginResult L = GetLoginResult();
	if (L.EntityToken.IsValid())
	{
		if (FEntityKey* E = L.EntityToken.Get()->Entity.Get())
		{
			D->SetStringField(TEXT("Id"), E->Id);
			D->SetStringField(TEXT("Type"), E->Type);
			D->SetStringField(TEXT("TypeString"), E->Type);
		}
	}
	return D;
}

FString APlayFabBaseActor::GetPlayFabId()
{
	return GetLoginResult().PlayFabId;
}

void APlayFabBaseActor::OnError(const PlayFab::FPlayFabCppError& ErrorResult) const
{
	FString Msg = FString::Printf(TEXT("PlayFabError: %s (%d)"), *ErrorResult.ErrorMessage, ErrorResult.ErrorCode);
	UKismetSystemLibrary::PrintString(GetWorld(), Msg, true, true, FLinearColor::Red);
	OnErrorMessage.Broadcast(Msg);
}

bool APlayFabBaseActor::IsLoggingIn()
{
	return GetLoginResult().AuthenticationContext.IsValid();
}
