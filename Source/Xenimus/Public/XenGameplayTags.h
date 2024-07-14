// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace FXenGameplayTags
{
#pragma region Vital Attributes
	XENIMUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Life);
	XENIMUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_MaxLife);
	XENIMUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Mana);
	XENIMUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_MaxMana);
#pragma endregion

#pragma region Primary Attributes
	XENIMUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Power);
	XENIMUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Dexterity);
	XENIMUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Vitality);
	XENIMUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Acuity);
	XENIMUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Wisdom);
#pragma endregion

#pragma region Statuses
	XENIMUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Life_Full);
	XENIMUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Life_Empty);
	XENIMUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Mana_Full);
	XENIMUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Mana_Empty);
	XENIMUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Ability_Queued);
#pragma endregion 
}
