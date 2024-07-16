// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "XenAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY() UAbilitySystemComponent *SourceASC = nullptr;
	UPROPERTY() AActor *SourceAvatarActor = nullptr;
	UPROPERTY() AController *SourceController = nullptr;
	UPROPERTY() ACharacter *SourceCharacter = nullptr;
	
	UPROPERTY() UAbilitySystemComponent *TargetASC = nullptr;
	UPROPERTY() AActor *TargetAvatarActor = nullptr;
	UPROPERTY() AController *TargetController = nullptr;
	UPROPERTY() ACharacter *TargetCharacter = nullptr;
};

template <class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class XENARTH_API UXenAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UXenAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	// A mapping between a gameplay tag and the function used to retrieve that attribute data
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagToAttribute;
	
private:
	static void SetEffectProperties(const FGameplayEffectModCallbackData &Data, FEffectProperties &Props);
	
// -----------------------------------------------------------------------------------------------------------------
// Vital Attributes
// -----------------------------------------------------------------------------------------------------------------
#pragma region Vital Attributes
public:
	ATTRIBUTE_ACCESSORS(UXenAttributeSet, Life);
	ATTRIBUTE_ACCESSORS(UXenAttributeSet, MaxLife);
	ATTRIBUTE_ACCESSORS(UXenAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(UXenAttributeSet, MaxMana);
	ATTRIBUTE_ACCESSORS(UXenAttributeSet, Stamina);
	ATTRIBUTE_ACCESSORS(UXenAttributeSet, MaxStamina);

protected:
	UFUNCTION() void OnRep_Life(const FGameplayAttributeData &OldValue) const;
	UFUNCTION() void OnRep_MaxLife(const FGameplayAttributeData &OldValue) const;
	UFUNCTION() void OnRep_Mana(const FGameplayAttributeData &OldValue) const;
	UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData &OldValue) const;
	UFUNCTION() void OnRep_Stamina(const FGameplayAttributeData &OldValue) const;
	UFUNCTION() void OnRep_MaxStamina(const FGameplayAttributeData &OldValue) const;
	
private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Life, Category = "Attribute|Vital")
	FGameplayAttributeData Life;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_MaxLife, Category = "Attribute|Vital")
	FGameplayAttributeData MaxLife;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Mana, Category = "Attribute|Vital")
	FGameplayAttributeData Mana;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_MaxMana, Category = "Attribute|Vital")
	FGameplayAttributeData MaxMana;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Stamina, Category = "Attribute|Vital")
	FGameplayAttributeData Stamina;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_MaxStamina, Category = "Attribute|Vital")
	FGameplayAttributeData MaxStamina;

	void LifePostGameplayEffect() const;
	void ManaPostGameplayEffect() const;
	void StaminaPostGameplayEffect() const;
#pragma endregion

// -----------------------------------------------------------------------------------------------------------------
// Primary Attributes
// -----------------------------------------------------------------------------------------------------------------
#pragma region Primary Attributes
public:
	ATTRIBUTE_ACCESSORS(UXenAttributeSet, Power);
	ATTRIBUTE_ACCESSORS(UXenAttributeSet, Dexterity);
	ATTRIBUTE_ACCESSORS(UXenAttributeSet, Vitality);
	ATTRIBUTE_ACCESSORS(UXenAttributeSet, Acuity);
	ATTRIBUTE_ACCESSORS(UXenAttributeSet, Wisdom);

protected:
	UFUNCTION() void OnRep_Power(const FGameplayAttributeData &OldValue) const;
	UFUNCTION() void OnRep_Dexterity(const FGameplayAttributeData &OldValue) const;
	UFUNCTION() void OnRep_Vitality(const FGameplayAttributeData &OldValue) const;
	UFUNCTION() void OnRep_Acuity(const FGameplayAttributeData &OldValue) const;
	UFUNCTION() void OnRep_Wisdom(const FGameplayAttributeData &OldValue) const;
	
private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Power, Category = "Attribute|Primary")
	FGameplayAttributeData Power;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Dexterity, Category = "Attribute|Primary")
	FGameplayAttributeData Dexterity;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Vitality, Category = "Attribute|Primary")
	FGameplayAttributeData Vitality;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Acuity, Category = "Attribute|Primary")
	FGameplayAttributeData Acuity;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Wisdom, Category = "Attribute|Primary")
	FGameplayAttributeData Wisdom;
#pragma endregion

// -----------------------------------------------------------------------------------------------------------------
// Secondary Attributes
// -----------------------------------------------------------------------------------------------------------------
#pragma region Secondary Attributes
public:
	ATTRIBUTE_ACCESSORS(UXenAttributeSet, MovementSpeed);
	
protected:
	UFUNCTION() void OnRep_MovementSpeed(const FGameplayAttributeData &OldValue) const;
	
private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_MovementSpeed, Category = "Attribute|Secondary")
	FGameplayAttributeData MovementSpeed;
#pragma endregion

// -----------------------------------------------------------------------------------------------------------------
// Meta Attributes
// -----------------------------------------------------------------------------------------------------------------
#pragma region Meta Attributes
public:
	ATTRIBUTE_ACCESSORS(UXenAttributeSet, IncomingDamage);
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Attribute|Meta")
	FGameplayAttributeData IncomingDamage;
	
	void DamagePostGameplayEffect(const FEffectProperties& Props);
#pragma endregion
};
