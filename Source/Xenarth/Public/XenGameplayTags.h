// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace FXenGameplayTags
{
#pragma region Vital Attributes
	Xenarth_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Life);
	Xenarth_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_MaxLife);
	Xenarth_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Mana);
	Xenarth_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_MaxMana);
#pragma endregion

#pragma region Primary Attributes
	Xenarth_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Power);
	Xenarth_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Dexterity);
	Xenarth_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Vitality);
	Xenarth_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Acuity);
	Xenarth_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Wisdom);
#pragma endregion

#pragma region Statuses
	Xenarth_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Life_Full);
	Xenarth_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Life_Empty);
	Xenarth_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Mana_Full);
	Xenarth_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Mana_Empty);
	Xenarth_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Ability_Queued);
#pragma endregion 
}
