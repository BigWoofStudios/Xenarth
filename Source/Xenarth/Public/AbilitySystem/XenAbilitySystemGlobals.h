// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "XenGameplayEffectContext.h"
#include "XenAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class XENARTH_API UXenAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
public:
    UXenAbilitySystemGlobals();
    virtual FGameplayEffectContext* AllocGameplayEffectContext() const override { return new FXenGameplayEffectContext(); }
};
