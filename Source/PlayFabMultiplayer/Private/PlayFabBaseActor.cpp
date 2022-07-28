// Copyright (C) 2022 Thinh Pham.


#include "PlayFabBaseActor.h"
#include "Kismet/KismetSystemLibrary.h"

APlayFabBaseActor::APlayFabBaseActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APlayFabBaseActor::BeginPlay()
{
	Super::BeginPlay();
}

void APlayFabBaseActor::PlayFapError(FPlayFabError Error, UObject* CustomData)
{
	FString Msg = FString::Printf(TEXT("PlayFabError: %s (%d)"), *Error.ErrorMessage, Error.ErrorCode);
	UKismetSystemLibrary::PrintString(GetWorld(), Msg, true, true, FLinearColor::Red);
	OnErrorMessage.Broadcast(Msg);
}
