// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "AbilitySystem/XenAbilitySystemGlobals.h"

#include "AbilitySystem/XenGameplayEffectContext.h"

UXenAbilitySystemGlobals::UXenAbilitySystemGlobals()
{
	ReplicateActivationOwnedTags = true;
}

FGameplayEffectContext* UXenAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FXenGameplayEffectContext();
}