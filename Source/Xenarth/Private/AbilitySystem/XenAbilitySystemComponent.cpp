// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "AbilitySystem/XenAbilitySystemComponent.h"

void UXenAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UXenAbilitySystemComponent::Client_EffectApplied);
}

void UXenAbilitySystemComponent::Client_EffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	GameplayEffectSpec.GetAllAssetTags(TagContainer);

	OnGameplayEffectAppliedDelegate.Broadcast(TagContainer);
}
