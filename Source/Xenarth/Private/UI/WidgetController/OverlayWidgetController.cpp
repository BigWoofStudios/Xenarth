// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/XenAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnLifeChanged.Broadcast(GetXenAttributeSet()->GetLife());
	OnMaxLifeChanged.Broadcast(GetXenAttributeSet()->GetMaxLife());
	OnMaxManaChanged.Broadcast(GetXenAttributeSet()->GetMaxMana());
	OnManaChanged.Broadcast(GetXenAttributeSet()->GetMana());
	OnMaxStaminaChanged.Broadcast(GetXenAttributeSet()->GetMaxStamina());
	OnStaminaChanged.Broadcast(GetXenAttributeSet()->GetStamina());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetXenAttributeSet()->GetLifeAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnLifeChanged.Broadcast(Data.NewValue);
			}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetXenAttributeSet()->GetMaxLifeAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxLifeChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetXenAttributeSet()->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetXenAttributeSet()->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetXenAttributeSet()->GetStaminaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnStaminaChanged.Broadcast(Data.NewValue);
			}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetXenAttributeSet()->GetMaxStaminaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxStaminaChanged.Broadcast(Data.NewValue);
			}
		);
}
