// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Player/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(const int32 InXP) const
{
	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		// LevelUpInformation[1] = Level 1 Information
		// LevelUpInformation[2] = Level 2 Information
		if (LevelUpInformation.Num() - 1 <= Level) return Level;

		if (InXP >= LevelUpInformation[Level].XPRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
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
