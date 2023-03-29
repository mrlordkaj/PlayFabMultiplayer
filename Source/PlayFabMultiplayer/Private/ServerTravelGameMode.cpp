// Copyright (C) 2022 Thinh Pham.


#include "ServerTravelGameMode.h"
#include "GSDKUtils.h"
#include "PlayFab.h"

using namespace PlayFab::MultiplayerModels;

void AServerTravelGameMode::BeginPlay()
{
	PlayFabMultiplayerPtr API = IPlayFabModuleInterface::Get().GetMultiplayerAPI();
	FGetMatchRequest R;
	R.MatchId = UGSDKUtils::GetMatchId();
	R.QueueName = TEXT("MahjongTestMap"); // TODO: move to settings
	R.ReturnMemberAttributes = true;
	API->GetMatch(R,
		PlayFab::UPlayFabMultiplayerAPI::FGetMatchDelegate::CreateUObject(this, &AServerTravelGameMode::GetMatchSuccess));
}

void AServerTravelGameMode::GetMatchSuccess(const FGetMatchResult& Result)
{
	if (!Result.Members.IsEmpty())
	{
		FMatchmakingPlayerWithTeamAssignment M = Result.Members[0];
	}
}
