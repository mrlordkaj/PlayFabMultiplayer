// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabBaseActor.h"
#include "PlayFabLoginActor.generated.h"

/**
 * 
 */
UCLASS()
class PLAYFABMULTIPLAYER_API APlayFabLoginActor : public APlayFabBaseActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FGenericDelegate OnLoginSuccess;

	UFUNCTION(BlueprintCallable)
	void LoginWithEmail(FString Email, FString Password);

private:
	void OnSuccess(const PlayFab::ClientModels::FLoginResult& Result);
};
