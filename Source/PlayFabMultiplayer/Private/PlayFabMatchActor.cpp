// Copyright (C) 2022 Thinh Pham.


#include "PlayFabMatchActor.h"

APlayFabMatchActor::APlayFabMatchActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.5f;
	
	RegionLatencies.Add(FRegionLatency("EastUS"));
	RegionLatencies.Add(FRegionLatency("NorthEurope"));
}
