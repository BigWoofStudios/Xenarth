// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "XenWidgetController.generated.h"

class UXenAttributeSet;
class UXenAbilitySystemComponent;
class AXenPlayerState;
class AXenPlayerController;
class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PlayerController, APlayerState* PlayerState, UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet)
	: PlayerController(PlayerController), PlayerState(PlayerState), AbilitySystemComponent(AbilitySystemComponent), AttributeSet(AttributeSet) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/**
 * 
 */
UCLASS()
class XENARTH_API UXenWidgetController : public UObject
{
	GENERATED_BODY()
public:
	void SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams);
	virtual void BroadcastInitialValues() { /* Used in inherited classes. */ };
	virtual void BindCallbacksToDependencies() { /* Used in inherited classes. */ };

	AXenPlayerController* GetXenPlayerController() const { return XenPlayerController; }
	AXenPlayerState* GetXenPlayerState() const { return XenPlayerState; }
	UXenAbilitySystemComponent* GetXenAbilitySystemComponent() const { return XenAbilitySystemComponent; }
	UXenAttributeSet* GetXenAttributeSet() const { return XenAttributeSet; }
	
protected:
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	UPROPERTY(VisibleAnywhere, Category="WidgetController")
	TObjectPtr<AXenPlayerController> XenPlayerController;

	UPROPERTY(VisibleAnywhere, Category="WidgetController")
	TObjectPtr<AXenPlayerState> XenPlayerState;

	UPROPERTY(VisibleAnywhere, Category="WidgetController")
	TObjectPtr<UXenAbilitySystemComponent> XenAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category="WidgetController")
	TObjectPtr<UXenAttributeSet> XenAttributeSet;
};
