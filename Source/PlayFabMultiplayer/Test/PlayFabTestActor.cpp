// Copyright (C) 2022 Thinh Pham.


#include "PlayFabTestActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#define PARAM_LOGIN_ID		TEXT("LoginId")
#define PARAM_LOGIN_TOKEN	TEXT("LoginToken")
#define PARAM_OPTIONS		TEXT("Options")
#define PARAM_PORTAL		TEXT("Portal")

using namespace PlayFab::ClientModels;

APlayFabTestActor::APlayFabTestActor()
{
	PlayFabLogin = CreateDefaultSubobject<UPlayFabLoginComponent>(TEXT("PlayFabLogin"));
}

void APlayFabTestActor::BeginPlay()
{
	Super::BeginPlay();

	FString Cmd = UKismetSystemLibrary::GetCommandLine();
	TArray<FString> Tokens;
	TArray<FString> Switches;
	TMap<FString, FString> Params;
	UKismetSystemLibrary::ParseCommandLine(Cmd, Tokens, Switches, Params);
	if (Params.Contains(PARAM_LOGIN_ID))
	{
		LoginId = *Params.Find(PARAM_LOGIN_ID);
	}
	if (Params.Contains(PARAM_LOGIN_TOKEN))
	{
		LoginToken = *Params.Find(PARAM_LOGIN_TOKEN);
	}
	if (Params.Contains(PARAM_OPTIONS))
	{
		Options = *Params.Find(PARAM_OPTIONS);
	}
	if (Params.Contains(PARAM_PORTAL)) {
		Portal = *Params.Find(PARAM_PORTAL);
	}
	if (!LoginId.IsEmpty() && !LoginToken.IsEmpty())
	{
		PlayFabLogin->OnLoginSuccess.AddDynamic(this, &APlayFabTestActor::LoginSuccess);
		switch (LoginMethod)
		{
		case EPlayFabLoginMethod::PlayFab:
			PlayFabLogin->LoginPlayFab(LoginId, LoginToken, false);
			break;

		case EPlayFabLoginMethod::EmailAddress:
			PlayFabLogin->LoginEmailAddress(LoginId, LoginToken, false);
			break;
		}
	}
}

void APlayFabTestActor::LoginSuccess()
{
	UGameplayStatics::OpenLevel(this, TEXT("127.0.0.1"), true,
		TEXT("PlayFabId=") + UPlayFabHelper::GetLoginPlayFabId(this) + Options + TEXT("#") + Portal);
}
