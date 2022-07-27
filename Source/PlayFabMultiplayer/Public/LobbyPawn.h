// Copyright (C) 2022 Thinh Pham.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LobbyPawn.generated.h"

UCLASS()
class PLAYFABMULTIPLAYER_API ALobbyPawn : public APawn
{
	GENERATED_BODY()

public:
	ALobbyPawn();

	/* Use to send target map to server lobby. */
	UPROPERTY(Replicated)
	FString ServerTargetMap;

protected:
	virtual void BeginPlay() override;

private:
	/* Use to send target map to server lobby. */
	UFUNCTION(Server, Unreliable)
	virtual void SubmitServerTargetMap(const FString& ClientTargetMap);

};
