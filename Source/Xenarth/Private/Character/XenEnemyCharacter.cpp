// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/XenEnemyCharacter.h"

#include "XenGameplayTags.h"
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

void AXenEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	// TODO: Cast<UXenAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();


	if (HasAuthority())
	{
		InitializeDefaultAttributes();		
	}
	// TODO: OnAscRegistered.Broadcast(AbilitySystemComponent);
}

void AXenEnemyCharacter::InitializeDefaultAttributes() const
{
	// TODO: Call a custom ability system BP library to InitializeDefaultAttributes with character details...
}
