// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "XenPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class XENIMUS_API AXenPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AXenPlayerState();
	
#pragma region IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
#pragma endregion
	
	UAttributeSet* GetAttributeSet() const { return AttributeSet; };
	
protected:
	UPROPERTY() TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY() TObjectPtr<UAttributeSet> AttributeSet;
};
