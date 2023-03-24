// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabSaveLogin.h"
#include "PlayFabBaseComponent.h"
#include "PlayFabLoginComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (PlayFab), meta = (BlueprintSpawnableComponent))
class PLAYFABMULTIPLAYER_API UPlayFabLoginComponent : public UPlayFabBaseComponent
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintAssignable)
	FDelegatePlayFabGeneric OnLoginSuccess;

	UFUNCTION(BlueprintCallable, DisplayName = "Register PlayFab")
	void RegisterPlayFab(FString Username, FString Email, FString Password);

	UFUNCTION(BlueprintCallable)
	bool LoginFromSave();

	UFUNCTION(BlueprintCallable, DisplayName = "Login PlayFab")
	void LoginPlayFab(FString Username, FString Password, bool bRemember = false);

	UFUNCTION(BlueprintCallable)
	void LoginEmailAddress(FString Email, FString Password, bool bRemember = false);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsValidUsername(FString Username);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsValidEmail(FString Email);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsValidPassword(FString Password);

private:
	bool bRememberMe;

	FRegisterPlayFabUserRequest RegisterRequest;

	UPROPERTY()
	UPlayFabSaveLogin* SaveLogin;

	void RegisterSuccess(const PlayFab::ClientModels::FRegisterPlayFabUserResult& Result);

	void LoginSuccess(const PlayFab::ClientModels::FLoginResult& Result);
};
