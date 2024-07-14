// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "XenGameplayTags.h"

namespace FXenGameplayTags
{
#pragma region Vital Attributes
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Vital_Life, FName{TEXT("Attribute.Vital.Life")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Vital_MaxLife, FName{TEXT("Attribute.Vital.MaxLife")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Vital_Mana, FName{TEXT("Attribute.Vital.Mana")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Vital_MaxMana, FName{TEXT("Attribute.Vital.MaxMana")});
#pragma endregion
	
#pragma region Primary Attributes
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Power, FName{TEXT("Attribute.Primary.Power")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Dexterity, FName{TEXT("Attribute.Primary.Dexterity")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Vitality, FName{TEXT("Attribute.Primary.Vitality")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Acuity, FName{TEXT("Attribute.Primary.Acuity")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Wisdom, FName{TEXT("Attribute.Primary.Wisdom")});
#pragma endregion
	
#pragma region Statuses
	UE_DEFINE_GAMEPLAY_TAG(Status_Attribute_Life_Full, FName{TEXT("Status.Attribute.Life.Full")});
	UE_DEFINE_GAMEPLAY_TAG(Status_Attribute_Life_Empty, FName{TEXT("Status.Attribute.Life.Empty")});
	UE_DEFINE_GAMEPLAY_TAG(Status_Attribute_Mana_Full, FName{TEXT("Status.Attribute.Mana.Full")});
	UE_DEFINE_GAMEPLAY_TAG(Status_Attribute_Mana_Empty, FName{TEXT("Status.Attribute.Mana.Empty")});
	
	UE_DEFINE_GAMEPLAY_TAG(Status_Ability_Queued, FName{TEXT("Status.Ability.Queued")});
#pragma endregion
}