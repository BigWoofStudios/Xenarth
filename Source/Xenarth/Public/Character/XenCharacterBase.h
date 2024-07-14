// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "XenCharacterBase.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class Xenarth_API AXenCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AXenCharacterBase();

#pragma region IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
#pragma endregion

	UAttributeSet* GetAttributeSet() const { return AttributeSet; };

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() {/* Used in inherited classes. */};
	UPROPERTY(VisibleAnywhere) TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere) TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category=Attributes)
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category=Attributes)
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

private:
	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, const float Level) const;
	void InitializeDefaultAttributes() const;
};
