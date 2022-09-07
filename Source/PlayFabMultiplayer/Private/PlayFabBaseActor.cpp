// Copyright (C) 2022 Thinh Pham.


#include "PlayFabBaseActor.h"
#include "PlayFabGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

APlayFabBaseActor::APlayFabBaseActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APlayFabBaseActor::PlayFapError(FPlayFabError Error, UObject* CustomData)
{
	FString Msg = FString::Printf(TEXT("PlayFabError: %s (%d)"), *Error.ErrorMessage, Error.ErrorCode);
	UKismetSystemLibrary::PrintString(GetWorld(), Msg, true, true, FLinearColor::Red);
	OnErrorMessage.Broadcast(Msg);
}

UPlayFabAuthenticationContext* APlayFabBaseActor::GetLoginContext()
{
	UPlayFabGameInstance* GInst = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GInst ? GInst->PlayFabLoginContext : nullptr;
}

UPlayFabJsonObject* APlayFabBaseActor::GetPlayFabEntity()
{
	UWorld* World = GetWorld();
	UPlayFabGameInstance* GInst = World->GetGameInstance<UPlayFabGameInstance>();
	return GInst ? GInst->PlayFabEntity : UPlayFabJsonObject::ConstructJsonObject(World);
}

FString APlayFabBaseActor::GetPlayFabId()
{
	UPlayFabGameInstance* GInst = GetWorld()->GetGameInstance<UPlayFabGameInstance>();
	return GInst ? GInst->PlayFabId : FString();
}
