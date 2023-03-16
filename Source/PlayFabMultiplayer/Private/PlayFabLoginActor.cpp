// Copyright (C) 2022 Thinh Pham.


#include "PlayFabLoginActor.h"

void APlayFabLoginActor::LoginWithEmail(FString Email, FString Password)
{
	PlayFab::ClientModels::FLoginWithEmailAddressRequest Request;
	Request.Email = Email;
	Request.Password = Password;
	ClientAPI->LoginWithEmailAddress(Request,
		PlayFab::UPlayFabClientAPI::FLoginWithEmailAddressDelegate::CreateUObject(this, &APlayFabLoginActor::OnSuccess),
		PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &APlayFabBaseActor::OnError)
	);
}

void APlayFabLoginActor::OnSuccess(const PlayFab::ClientModels::FLoginResult& Result)
{
	if (UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>())
	{
		GI->PlayFabLogin = Result;
		OnLoginSuccess.Broadcast();
	}
}
