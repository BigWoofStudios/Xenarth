// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Player/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(const int32 InXP) const
{
	int32 Low = 1;
	int32 High = LevelUpInformation.Num() - 1;

	while (Low <= High)
	{
		const int32 Mid = (Low + High) / 2;

		if (LevelUpInformation[Mid].XPRequirement == InXP)
		{
			return Mid;
		}
		
		if (LevelUpInformation[Mid].XPRequirement < InXP)
		{
			Low = Mid + 1;
		}
		else
		{
			High = Mid - 1;
		}
	}

	return Low;
}

int32 ULevelUpInfo::FindRequiredXPForNextLevel(const int32 InLevel) const
{
	if (LevelUpInformation.IsValidIndex(InLevel + 1))
	{
		return LevelUpInformation[InLevel + 1].XPRequirement;
	}

	return MAX_int32;
}
