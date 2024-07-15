// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Player/XenPlayerState.h"

#include "AbilitySystem/XenAbilitySystemComponent.h"
#include "AbilitySystem/XenAttributeSet.h"

AXenPlayerState::AXenPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UXenAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UXenAttributeSet>(TEXT("AttributeSet"));
}
