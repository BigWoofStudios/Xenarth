// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "AbilitySystem/XenAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "XenGameplayTags.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UXenAttributeSet::UXenAttributeSet()
{
	TagToAttribute.Add(FXenGameplayTags::Attribute_Vital_Health, GetHealthAttribute);
	TagToAttribute.Add(FXenGameplayTags::Attribute_Vital_MaxHealth, GetMaxHealthAttribute);
}

void UXenAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UXenAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXenAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UXenAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute()) NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
}

void UXenAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (GetIncomingDamageAttribute() == Data.EvaluatedData.Attribute)
	{
		DamagePostGameplayEffect(Props);
	}
	
	if (TSet{GetHealthAttribute(), GetMaxHealthAttribute()}.Contains(Data.EvaluatedData.Attribute))
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	
	HealthPostGameplayEffect();
}

void UXenAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
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
		const float NewHealth = GetHealth() - LocalIncomingDamage;
		SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

		if (NewHealth <= 0.f)
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

void UXenAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) const  { GAMEPLAYATTRIBUTE_REPNOTIFY(UXenAttributeSet, Health, OldValue); }
void UXenAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const  { GAMEPLAYATTRIBUTE_REPNOTIFY(UXenAttributeSet, MaxHealth, OldValue); }

void UXenAttributeSet::HealthPostGameplayEffect() const
{
	const UAbilitySystemComponent *ASC = GetOwningAbilitySystemComponent();
	if (!ASC) return;

	AActor* OwningActor = GetOwningActor();
	if (!OwningActor) return;
	
	const bool bIsEmpty = ASC->HasMatchingGameplayTag(FXenGameplayTags::Status_Attribute_Health_Empty);
	const bool bIsFull = ASC->HasMatchingGameplayTag(FXenGameplayTags::Status_Attribute_Health_Full);
	
	if (GetHealth() <= 0.f && !bIsEmpty)
	{
		UAbilitySystemBlueprintLibrary::AddLooseGameplayTags(OwningActor, FGameplayTagContainer{FXenGameplayTags::Status_Attribute_Health_Empty}, true);
	}
	else if (GetHealth() > 0.f && bIsEmpty)
	{
		UAbilitySystemBlueprintLibrary::RemoveLooseGameplayTags(OwningActor, FGameplayTagContainer{FXenGameplayTags::Status_Attribute_Health_Empty}, true);
	}

	if (GetHealth() >= GetMaxHealth() && !bIsFull)
	{
		UAbilitySystemBlueprintLibrary::AddLooseGameplayTags(OwningActor, FGameplayTagContainer{FXenGameplayTags::Status_Attribute_Health_Full}, true);
	}
	else if (GetHealth() < GetMaxHealth() && bIsFull)
	{
		UAbilitySystemBlueprintLibrary::RemoveLooseGameplayTags(OwningActor, FGameplayTagContainer{FXenGameplayTags::Status_Attribute_Health_Full}, true);
	}
}

