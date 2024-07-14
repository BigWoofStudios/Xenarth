// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "XenAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class Xenarth_API UXenAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
    UXenAbilitySystemGlobals();
    virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
