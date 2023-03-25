// Copyright (C) 2022 Thinh Pham.


#include "PlayFabHelper.h"

bool UPlayFabHelper::IsValidUsername(FString Username)
{
	FRegexPattern P(TEXT("[\\w\\d]{4,64}"));
	FRegexMatcher M(P, Username);
	return M.FindNext();
}

bool UPlayFabHelper::IsValidEmail(FString Email)
{
	FRegexPattern P(TEXT("[\\w\\d]{3,}@[\\w\\d]+\\.[\\w\\d]{2,}"));
	FRegexMatcher M(P, Email);
	return M.FindNext();
}

bool UPlayFabHelper::IsValidPassword(FString Password)
{
	return Password.Len() >= 3;
}
