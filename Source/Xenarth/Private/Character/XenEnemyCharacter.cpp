// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/XenEnemyCharacter.h"

#include "AbilitySystem/XenAbilitySystemComponent.h"
#include "AbilitySystem/XenAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"

AXenEnemyCharacter::AXenEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UXenAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UXenAttributeSet>(TEXT("AttributeSet"));
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void AXenEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	checkf(AbilitySystemComponent, TEXT("AbilitySystemComponent is null in AXenEnemyCharacter::BeginPlay"));
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
