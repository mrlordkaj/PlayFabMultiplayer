// Copyright (C) 2022 Thinh Pham.


#include "PlayFabLoginComponent.h"
#include "PlayFabGameInstance.h"
#include "PlayFabMultiplayer.h"
#include "Kismet/GameplayStatics.h"

#define LOGIN_SAVE_SLOT TEXT("PlayFabLogin")

using namespace PlayFab::ClientModels;

void UPlayFabLoginComponent::BeginPlay()
{
	Super::BeginPlay();

	SaveLogin = NewObject<UPlayFabSaveLogin>(this);
}

void UPlayFabLoginComponent::RegisterPlayFab(FString Username, FString Email, FString Password)
{
	RegisterRequest.Username = Username;
	RegisterRequest.Email = Email;
	RegisterRequest.Password = Password;
	RegisterRequest.RequireBothUsernameAndEmail = true;
	ClientAPI->RegisterPlayFabUser(RegisterRequest,
		PlayFab::UPlayFabClientAPI::FRegisterPlayFabUserDelegate::CreateUObject(this, &UPlayFabLoginComponent::RegisterSuccess),
		DefaultErrorCpp);
}

bool UPlayFabLoginComponent::LoginFromSave()
{
	USaveGame* S = UGameplayStatics::LoadGameFromSlot(LOGIN_SAVE_SLOT, 0);
	if (UPlayFabSaveLogin* L = Cast<UPlayFabSaveLogin>(S)) {
		switch (L->Method) {
		case EPlayFabLoginMethod::PlayFab:
			LoginPlayFab(L->Identity, L->Token);
			break;

		case EPlayFabLoginMethod::EmailAddress:
			LoginEmailAddress(L->Identity, L->Token);
		}
		SaveLogin = L;
		return true;
	}
	return false;
}

void UPlayFabLoginComponent::RegisterSuccess(const PlayFab::ClientModels::FRegisterPlayFabUserResult& Result)
{
	// auto login after register
	LoginPlayFab(RegisterRequest.Username, RegisterRequest.Password);
}

void UPlayFabLoginComponent::LoginPlayFab(FString Username, FString Password, bool bRemember)
{
	FLoginWithPlayFabRequest R;
	SaveLogin->Method = EPlayFabLoginMethod::PlayFab;
	SaveLogin->Identity = R.Username = Username;
	SaveLogin->Token = R.Password = Password;
	bRememberMe = bRemember;
	ClientAPI->LoginWithPlayFab(R,
		PlayFab::UPlayFabClientAPI::FLoginWithEmailAddressDelegate::CreateUObject(this, &UPlayFabLoginComponent::LoginSuccess),
		DefaultErrorCpp);
}

void UPlayFabLoginComponent::LoginEmailAddress(FString Email, FString Password, bool bRemember)
{
	FLoginWithEmailAddressRequest R;
	SaveLogin->Method = EPlayFabLoginMethod::EmailAddress;
	SaveLogin->Identity = R.Email = Email;
	SaveLogin->Token = R.Password = Password;
	bRememberMe = bRemember;
	ClientAPI->LoginWithEmailAddress(R,
		PlayFab::UPlayFabClientAPI::FLoginWithEmailAddressDelegate::CreateUObject(this, &UPlayFabLoginComponent::LoginSuccess),
		DefaultErrorCpp);
}

void UPlayFabLoginComponent::Logout()
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	GI->AuthenticationContext = nullptr;
	GI->PlayFabId = TEXT("");
	GI->EntityId = TEXT("");
	UGameplayStatics::DeleteGameInSlot(LOGIN_SAVE_SLOT, 0);
}

void UPlayFabLoginComponent::LoginSuccess(const FLoginResult& Result)
{
	UPlayFabGameInstance* GI = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	GI->AuthenticationContext = Result.AuthenticationContext;
	GI->PlayFabId = Result.PlayFabId;
	if (Result.EntityToken.IsValid()) {
		GI->EntityId = Result.EntityToken->Entity->Id;
	}
	if (bRememberMe) {
		UGameplayStatics::SaveGameToSlot(SaveLogin, LOGIN_SAVE_SLOT, 0);
	}
	OnLoginSuccess.Broadcast();
}
