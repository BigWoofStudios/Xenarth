// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "XenAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameplayEffectApplied, const FGameplayTagContainer& /*AssetTags*/);

/**
 * 
 */
UCLASS()
class XENARTH_API UXenAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();
	
	FOnGameplayEffectApplied OnGameplayEffectAppliedDelegate;
	
protected:
	/**
	 * This is a reliable client-only function that gets called when a gameplay effect is applied to this AbilitySystemComponent.
	 * Triggers a broadcast of the gameplay effect's asset tags which can be used for UI updates and other client-side effects.
	 */
	UFUNCTION(Client, Reliable)
	void Client_EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
