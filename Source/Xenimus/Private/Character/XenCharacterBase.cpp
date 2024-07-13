// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/XenCharacterBase.h"

AXenCharacterBase::AXenCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

UAbilitySystemComponent* AXenCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AXenCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}
