// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Player/XenPlayerState.h"

#include "AbilitySystem/XenAbilitySystemComponent.h"
#include "AbilitySystem/XenAttributeSet.h"
#include "Net/UnrealNetwork.h"

AXenPlayerState::AXenPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UXenAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UXenAttributeSet>(TEXT("AttributeSet"));
}

void AXenPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	FDoRepLifetimeParams Parameters;
	
	Parameters.bIsPushBased = true;
	Parameters.RepNotifyCondition = REPNOTIFY_OnChanged;
	
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, CharacterName, Parameters);
}

