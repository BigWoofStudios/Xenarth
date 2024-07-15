// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace FXenGameplayTags
{
#pragma region Vital Attributes
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Life);
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_MaxLife);
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Mana);
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_MaxMana);
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Stamina);
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_MaxStamina);
#pragma endregion

#pragma region Primary Attributes
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Power);
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Dexterity);
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Vitality);
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Acuity);
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Wisdom);
#pragma endregion

#pragma region Secondary Attributes
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_MovementSpeed);
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_MaxMovementSpeed);
#pragma endregion
	
#pragma region Statuses
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Life_Full);
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Life_Empty);
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Mana_Full);
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Mana_Empty);
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Stamina_Full);
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Stamina_Empty);
	XENARTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Ability_Queued);
#pragma endregion 
}
