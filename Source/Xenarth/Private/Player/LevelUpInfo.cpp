// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Player/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(const int32 InXP) const
{
	int32 Level = 1;
	while (Level < LevelUpInformation.Num() && InXP >= LevelUpInformation[Level].XPRequirement)
	{
		++Level;
	}
	return Level;
}

int32 ULevelUpInfo::FindRequiredXPForNextLevel(const int32 InLevel) const
{
	if (LevelUpInformation.IsValidIndex(InLevel + 1))
	{
		return LevelUpInformation[InLevel + 1].XPRequirement;
	}

	return MAX_int32;
}
