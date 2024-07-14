// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/XenCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/XenGameplayEffectContext.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AXenCharacterBase::AXenCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
}

void AXenCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AXenCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, const float Level) const
{
	checkf(AbilitySystemComponent, TEXT("AbilitySystemComponent is not set in %s"), *GetName());
	checkf(GameplayEffectClass, TEXT("No GameplayEffectClass argument found for ApplyEffectToSelf in %s"), *GetName());
	
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	ContextHandle.AddSourceObject(this);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), AbilitySystemComponent);

}

void AXenCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
}
