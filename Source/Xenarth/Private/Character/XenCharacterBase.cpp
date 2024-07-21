// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/XenCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/XenAttributeSet.h"
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
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 900.0f, 0.0f);
}

void AXenCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	if (const UXenAttributeSet* XenAttributeSet = Cast<UXenAttributeSet>(AttributeSet))
	{
		SR_SetMovementSpeed();
		if (HasAuthority())
		{
			/* Change character's `Max<EMovementMode>Speed` based on MovementSpeed attribute. */
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(XenAttributeSet->GetMovementSpeedAttribute()).AddLambda(
				[this](const FOnAttributeChangeData& Data)
				{
					SetMovementSpeed(Data.NewValue);
					MC_SetMovementSpeed(Data.NewValue);
				}
			);
		}
	}
	
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

void AXenCharacterBase::SetMovementSpeed(const float InMovementSpeed) const
{
	GetCharacterMovement()->MaxWalkSpeed = InMovementSpeed;
	GetCharacterMovement()->MaxSwimSpeed = InMovementSpeed;
	GetCharacterMovement()->MaxFlySpeed = InMovementSpeed;
}

void AXenCharacterBase::SR_SetMovementSpeed_Implementation()
{
	if (const UXenAttributeSet* XenAttributeSet = Cast<UXenAttributeSet>(AttributeSet))
	{
		const float MovementSpeed = XenAttributeSet->GetMovementSpeed();
		SetMovementSpeed(MovementSpeed);
		MC_SetMovementSpeed(MovementSpeed);
	}
}

void AXenCharacterBase::MC_SetMovementSpeed_Implementation(const float InMovementSpeed)
{
	SetMovementSpeed(InMovementSpeed);
}

void AXenCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
}
