// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "Data/CharacterClassInfo.h"
#include "GameFramework/Character.h"
#include "XenCharacterBase.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class XENARTH_API AXenCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AXenCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	UAttributeSet* GetAttributeSet() const { return AttributeSet; };

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() {/* Used in inherited classes. */};
	virtual void InitializeDefaultAttributes() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Defaults")
	ECharacterClass CharacterClass = ECharacterClass::None;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Ability System")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Ability System")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Ability System")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Ability System")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Ability System")
	TSubclassOf<UGameplayAbility> DefaultAbilities;

private:
	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, const float Level) const;

	void SetMovementSpeed(const float InMovementSpeed) const;
	
	UFUNCTION(Server, Reliable)
	void SR_SetMovementSpeed();

	UFUNCTION(NetMulticast, Reliable)
	void MC_SetMovementSpeed(const float InMovementSpeed);
};
