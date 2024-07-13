// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "XenGameplayTags.h"

namespace FXenGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Vital_Health, FName{TEXT("Attribute.Vital.Health")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Vital_MaxHealth, FName{TEXT("Attribute.Vital.MaxHealth")});

	UE_DEFINE_GAMEPLAY_TAG(Status_Attribute_Health_Full, FName{TEXT("Status.Attribute.Health.Full")});
	UE_DEFINE_GAMEPLAY_TAG(Status_Attribute_Health_Empty, FName{TEXT("Status.Attribute.Health.Empty")});
}