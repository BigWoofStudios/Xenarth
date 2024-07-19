// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/XenAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnLifeChanged.Broadcast(GetXenAttributeSet()->GetLife());
	OnMaxLifeChanged.Broadcast(GetXenAttributeSet()->GetMaxLife());
	OnManaChanged.Broadcast(GetXenAttributeSet()->GetMana());
	OnMaxManaChanged.Broadcast(GetXenAttributeSet()->GetMaxMana());
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
}
