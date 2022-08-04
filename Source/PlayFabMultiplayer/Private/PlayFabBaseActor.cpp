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
	if (const UPlayFabGameInstance* GInst = GetWorld()->GetGameInstance<UPlayFabGameInstance>())
	{
		return GInst->PlayFabLoginContext;
	}
	return nullptr;
}

UPlayFabJsonObject* APlayFabBaseActor::GetPlayFabEntity()
{
	UPlayFabJsonObject* Entity = nullptr;
	UWorld* World = GetWorld();
	if (const UPlayFabGameInstance* GInst = World->GetGameInstance<UPlayFabGameInstance>())
	{
		Entity = GInst->PlayFabEntity;
	}
	return Entity ? Entity : UPlayFabJsonObject::ConstructJsonObject(World);
}

FString APlayFabBaseActor::GetPlayFabId()
{
	FString Id;
	if (const UPlayFabGameInstance* GInst = GetWorld()->GetGameInstance<UPlayFabGameInstance>())
	{
		Id = GInst->PlayFabId;
	}
	return Id;
}
