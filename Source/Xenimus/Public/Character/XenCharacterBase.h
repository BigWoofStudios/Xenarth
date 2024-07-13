// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "XenCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class XENIMUS_API AXenCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AXenCharacterBase();

#pragma region IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
#pragma endregion
	
	UAttributeSet* GetAttributeSet() const { return AttributeSet; };

protected:
	virtual void BeginPlay() override;

	UPROPERTY() TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY() TObjectPtr<UAttributeSet> AttributeSet;
};
