// Copyright (C) 2022 Thinh Pham.


#include "PlayFabLoginActor.h"
#include "PlayFabGameInstance.h"
#include "PlayFabMultiplayer.h"

using namespace PlayFab::ClientModels;

void APlayFabLoginActor::LoginWithEmail(FString Email, FString Password)
{
	FLoginWithEmailAddressRequest Request;
	Request.Email = Email;
	Request.Password = Password;
	ClientAPI->LoginWithEmailAddress(Request,
		PlayFab::UPlayFabClientAPI::FLoginWithEmailAddressDelegate::CreateUObject(this, &APlayFabLoginActor::OnSuccess),
		PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &APlayFabBaseActor::OnError)
	);
}

void APlayFabLoginActor::OnSuccess(const FLoginResult& Result)
{
	if (UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>())
	{
		GI->PlayFabLogin = Result;
		OnLoginSuccess.Broadcast();
	}
	else
	{
		UE_LOG(PlayFabMultiplayer, Error, TEXT("Missing PlayFabGameInstance."));
	}
}
