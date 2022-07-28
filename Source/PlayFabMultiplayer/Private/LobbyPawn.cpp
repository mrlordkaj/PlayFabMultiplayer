// Copyright (C) 2022 Thinh Pham.


#include "LobbyPawn.h"
#include "PlayFabGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

ALobbyPawn::ALobbyPawn()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALobbyPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyPawn, ServerTargetMap);
}

void ALobbyPawn::BeginPlay()
{
	Super::BeginPlay();

	// read target map from game instance
	UWorld* World = GetWorld();
	if (!HasAuthority() && UGameplayStatics::GetPlayerPawn(World, 0) == this)
	{
		UPlayFabGameInstance* GInst = Cast<UPlayFabGameInstance>(UGameplayStatics::GetGameInstance(World));
		if (GInst)
		{
			SubmitServerTargetMap(GInst->ServerTargetMap);
		}
	}
}

void ALobbyPawn::SubmitServerTargetMap_Implementation(const FString& ClientTargetMap)
{
	ServerTargetMap = ClientTargetMap;
}
