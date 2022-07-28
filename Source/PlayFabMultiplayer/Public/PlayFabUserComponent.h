// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/PlayFabClientAPI.h"
#include "Core/PlayFabError.h"
#include "PlayFabUserComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(PlayFabMultiplayer), meta=(BlueprintSpawnableComponent))
class PLAYFABMULTIPLAYER_API UPlayFabUserComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayFabUserComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	/* PlayerID used in title only. */
	UPROPERTY(BlueprintReadOnly, Replicated)
	FString PlayFabId;

	UPROPERTY(BlueprintReadOnly)
	FString DisplayName;

private:
	/* Use to send target map to server lobby. */
	UFUNCTION(Server, Unreliable)
	virtual void SubmitPlayFabId(const FString& ClientPlayFabId);

protected:
	/* List samples of PlayFabId for testing on local. */
	UPROPERTY(EditDefaultsOnly, Category = "Debugging")
	TArray<FString> DemoPlayFabUsers;

public:
	void OnGetPlayerProfileSuccess(const PlayFab::ClientModels::FGetPlayerProfileResult& Result);
	void OnPlayFabError(const PlayFab::FPlayFabCppError& ErrorResult);
};
