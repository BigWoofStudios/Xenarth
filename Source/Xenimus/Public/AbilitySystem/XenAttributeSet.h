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
class XENIMUS_API UXenAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UXenAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	// A mapping between a gameplay tag and the function used to retrieve that attribute data
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagToAttribute;
	
private:
	static void SetEffectProperties(const FGameplayEffectModCallbackData &Data, FEffectProperties &Props);
	
// -----------------------------------------------------------------------------------------------------------------
// Vital Attributes
// -----------------------------------------------------------------------------------------------------------------
#pragma region Vital Attributes
public:
	ATTRIBUTE_ACCESSORS(UXenAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UXenAttributeSet, MaxHealth);

protected:
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData &OldValue) const;
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData &OldValue) const;
	
private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Health, Category = "Attribute|Vital")
	FGameplayAttributeData Health;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_MaxHealth, Category = "Attribute|Vital")
	FGameplayAttributeData MaxHealth;

	void HealthPostGameplayEffect() const;
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
