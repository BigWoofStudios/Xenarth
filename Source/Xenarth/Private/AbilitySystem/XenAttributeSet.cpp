// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "AbilitySystem/XenAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "XenGameplayTags.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UXenAttributeSet::UXenAttributeSet()
{
#pragma region Vital Attributes
	TagToAttribute.Add(FXenGameplayTags::Attribute_Vital_Life, GetLifeAttribute);
	TagToAttribute.Add(FXenGameplayTags::Attribute_Vital_MaxLife, GetMaxLifeAttribute);
	TagToAttribute.Add(FXenGameplayTags::Attribute_Vital_Mana, GetManaAttribute);
	TagToAttribute.Add(FXenGameplayTags::Attribute_Vital_MaxMana, GetMaxManaAttribute);
	TagToAttribute.Add(FXenGameplayTags::Attribute_Vital_Stamina, GetStaminaAttribute);
	TagToAttribute.Add(FXenGameplayTags::Attribute_Vital_MaxStamina, GetMaxStaminaAttribute);
#pragma endregion 
	
#pragma region Primary Attributes
	TagToAttribute.Add(FXenGameplayTags::Attribute_Primary_Power, GetPowerAttribute);
	TagToAttribute.Add(FXenGameplayTags::Attribute_Primary_Dexterity, GetDexterityAttribute);
	TagToAttribute.Add(FXenGameplayTags::Attribute_Primary_Vitality, GetVitalityAttribute);
	TagToAttribute.Add(FXenGameplayTags::Attribute_Primary_Acuity, GetAcuityAttribute);
	TagToAttribute.Add(FXenGameplayTags::Attribute_Primary_Wisdom, GetWisdomAttribute);
#pragma endregion
	
#pragma region Secondary Attributes
	TagToAttribute.Add(FXenGameplayTags::Attribute_Secondary_MovementSpeed, GetMovementSpeedAttribute);
#pragma endregion
}

void UXenAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
#pragma region Vital Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UXenAttributeSet, Life, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXenAttributeSet, MaxLife, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXenAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXenAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXenAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXenAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
#pragma endregion
	
#pragma region Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UXenAttributeSet, Power, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXenAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXenAttributeSet, Vitality, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXenAttributeSet, Acuity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXenAttributeSet, Wisdom, COND_None, REPNOTIFY_Always);
#pragma endregion

#pragma region Secondary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UXenAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
#pragma endregion
}

void UXenAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetLifeAttribute()) NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxLife());
	if (Attribute == GetManaAttribute()) NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	if (Attribute == GetStaminaAttribute()) NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
	if (Attribute == GetMovementSpeedAttribute()) NewValue = FMath::Clamp(NewValue, 0.0f, AbsoluteMaxMovementSpeed);
}

void UXenAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetLifeAttribute())
	{
		SetLife(FMath::Clamp(GetLife(), 0.f, GetMaxLife()));
	}
	LifePostGameplayEffect();

	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		DamagePostGameplayEffect(Props);
	}
	
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	ManaPostGameplayEffect();
	
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
	}
	StaminaPostGameplayEffect();
	
	if (Data.EvaluatedData.Attribute == GetMovementSpeedAttribute())
	{
		SetMovementSpeed(FMath::Clamp(GetMovementSpeed(), 0.f, AbsoluteMaxMovementSpeed));
	}
}

void UXenAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn *Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UXenAttributeSet::DamagePostGameplayEffect(const FEffectProperties& Props)
{
	const float LocalIncomingDamage = GetIncomingDamage();
	SetIncomingDamage(0.f);

	// @TODO: Implement critical hit, floating text, and other effects
	// const bool bCriticalHit = UXenAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle);
		
	if (LocalIncomingDamage > 0.f)
	{
		FGameplayTagContainer TagContainer;
		const float NewLife = GetLife() - LocalIncomingDamage;
		SetLife(FMath::Clamp(NewLife, 0.f, GetMaxLife()));

		if (NewLife <= 0.f)
		{
			// TagContainer.AddTagFast(FXenGameplayTags::GameplayAbility_Death);
			Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
		}
		else
		{
			// TagContainer.AddTagFast(FXenGameplayTags::GameplayAbility_HitReact);
			Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
		}
	}
	
	// ShowFloatingText(Props, LocalIncomingDamage, bCriticalHit);
}

// ---------------------------------------------------------------------------------------------------------------------
// Vital Attributes
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Vital Attributes
void UXenAttributeSet::OnRep_Life(const FGameplayAttributeData& OldValue) const  { GAMEPLAYATTRIBUTE_REPNOTIFY(UXenAttributeSet, Life, OldValue); }
void UXenAttributeSet::OnRep_MaxLife(const FGameplayAttributeData& OldValue) const  { GAMEPLAYATTRIBUTE_REPNOTIFY(UXenAttributeSet, MaxLife, OldValue); }
void UXenAttributeSet::LifePostGameplayEffect() const
{
	const UAbilitySystemComponent *ASC = GetOwningAbilitySystemComponent();
	if (!ASC) return;

	AActor* OwningActor = GetOwningActor();
	if (!OwningActor) return;
	
	const bool bIsEmpty = ASC->HasMatchingGameplayTag(FXenGameplayTags::Status_Attribute_Life_Empty);
	const bool bIsFull = ASC->HasMatchingGameplayTag(FXenGameplayTags::Status_Attribute_Life_Full);
	
	if (GetLife() <= 0.f && !bIsEmpty)
	{
		UAbilitySystemBlueprintLibrary::AddLooseGameplayTags(OwningActor, FGameplayTagContainer{FXenGameplayTags::Status_Attribute_Life_Empty}, true);
	}
	else if (GetLife() > 0.f && bIsEmpty)
	{
		UAbilitySystemBlueprintLibrary::RemoveLooseGameplayTags(OwningActor, FGameplayTagContainer{FXenGameplayTags::Status_Attribute_Life_Empty}, true);
	}

	if (GetLife() >= GetMaxLife() && !bIsFull)
	{
		UAbilitySystemBlueprintLibrary::AddLooseGameplayTags(OwningActor, FGameplayTagContainer{FXenGameplayTags::Status_Attribute_Life_Full}, true);
	}
	else if (GetLife() < GetMaxLife() && bIsFull)
	{
		UAbilitySystemBlueprintLibrary::RemoveLooseGameplayTags(OwningActor, FGameplayTagContainer{FXenGameplayTags::Status_Attribute_Life_Full}, true);
	}
}

void UXenAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue) const  { GAMEPLAYATTRIBUTE_REPNOTIFY(UXenAttributeSet, Mana, OldValue); }
void UXenAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue) const  { GAMEPLAYATTRIBUTE_REPNOTIFY(UXenAttributeSet, MaxMana, OldValue); }
void UXenAttributeSet::ManaPostGameplayEffect() const
{
	const UAbilitySystemComponent *ASC = GetOwningAbilitySystemComponent();
	if (!ASC) return;

	AActor* OwningActor = GetOwningActor();
	if (!OwningActor) return;
	
	const bool bIsEmpty = ASC->HasMatchingGameplayTag(FXenGameplayTags::Status_Attribute_Mana_Empty);
	const bool bIsFull = ASC->HasMatchingGameplayTag(FXenGameplayTags::Status_Attribute_Mana_Full);
	
	if (GetMana() <= 0.f && !bIsEmpty)
	{
		UAbilitySystemBlueprintLibrary::AddLooseGameplayTags(OwningActor, FGameplayTagContainer{FXenGameplayTags::Status_Attribute_Mana_Empty}, true);
	}
	else if (GetMana() > 0.f && bIsEmpty)
	{
		UAbilitySystemBlueprintLibrary::RemoveLooseGameplayTags(OwningActor, FGameplayTagContainer{FXenGameplayTags::Status_Attribute_Mana_Empty}, true);
	}

	if (GetMana() >= GetMaxMana() && !bIsFull)
	{
		UAbilitySystemBlueprintLibrary::AddLooseGameplayTags(OwningActor, FGameplayTagContainer{FXenGameplayTags::Status_Attribute_Mana_Full}, true);
	}
	else if (GetMana() < GetMaxMana() && bIsFull)
	{
		UAbilitySystemBlueprintLibrary::RemoveLooseGameplayTags(OwningActor, FGameplayTagContainer{FXenGameplayTags::Status_Attribute_Mana_Full}, true);
	}
}

void UXenAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(UXenAttributeSet, Stamina, OldValue); }
void UXenAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(UXenAttributeSet, MaxStamina, OldValue); }
void UXenAttributeSet::StaminaPostGameplayEffect() const
{
	const UAbilitySystemComponent *ASC = GetOwningAbilitySystemComponent();
	if (!ASC) return;

	AActor* OwningActor = GetOwningActor();
	if (!OwningActor) return;
	
	const bool bIsEmpty = ASC->HasMatchingGameplayTag(FXenGameplayTags::Status_Attribute_Stamina_Empty);
	const bool bIsFull = ASC->HasMatchingGameplayTag(FXenGameplayTags::Status_Attribute_Stamina_Full);
	
	if (GetStamina() <= 0.f && !bIsEmpty)
	{
		UAbilitySystemBlueprintLibrary::AddLooseGameplayTags(OwningActor, FGameplayTagContainer{FXenGameplayTags::Status_Attribute_Stamina_Empty}, true);
	}
	else if (GetStamina() > 0.f && bIsEmpty)
	{
		UAbilitySystemBlueprintLibrary::RemoveLooseGameplayTags(OwningActor, FGameplayTagContainer{FXenGameplayTags::Status_Attribute_Stamina_Empty}, true);
	}

	if (GetStamina() >= GetMaxStamina() && !bIsFull)
	{
		UAbilitySystemBlueprintLibrary::AddLooseGameplayTags(OwningActor, FGameplayTagContainer{FXenGameplayTags::Status_Attribute_Stamina_Full}, true);
	}
	else if (GetStamina() < GetMaxStamina() && bIsFull)
	{
		UAbilitySystemBlueprintLibrary::RemoveLooseGameplayTags(OwningActor, FGameplayTagContainer{FXenGameplayTags::Status_Attribute_Stamina_Full}, true);
	}
}
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Primary Attributes
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Primary Attributes
void UXenAttributeSet::OnRep_Power(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(UXenAttributeSet, Power, OldValue); }
void UXenAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(UXenAttributeSet, Dexterity, OldValue); }
void UXenAttributeSet::OnRep_Vitality(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(UXenAttributeSet, Vitality, OldValue); }
void UXenAttributeSet::OnRep_Acuity(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(UXenAttributeSet, Acuity, OldValue); }
void UXenAttributeSet::OnRep_Wisdom(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(UXenAttributeSet, Wisdom, OldValue); }
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Secondary Attributes
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Secondary Attributes
void UXenAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldValue) const { GAMEPLAYATTRIBUTE_REPNOTIFY(UXenAttributeSet, MovementSpeed, OldValue); }
#pragma endregion 