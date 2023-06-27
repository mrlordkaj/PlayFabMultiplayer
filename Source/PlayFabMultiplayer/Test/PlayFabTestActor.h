// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabTypes.h"
#include "PlayFabBaseActor.h"
#include "PlayFabLoginComponent.h"
#include "PlayFabTestActor.generated.h"

/**
 * 
 */
UCLASS()
class PLAYFABMULTIPLAYER_API APlayFabTestActor : public APlayFabBaseActor
{
	GENERATED_BODY()
	
protected:
	APlayFabTestActor();

	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UPlayFabLoginComponent* PlayFabLogin;

	UPROPERTY(EditAnywhere)
	EPlayFabLoginMethod LoginMethod = EPlayFabLoginMethod::PlayFab;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	FString LoginId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FString LoginToken;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FString Options;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FString Portal;

	UFUNCTION()
	void LoginSuccess();
};
