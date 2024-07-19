// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "UI/WidgetController/XenWidgetController.h"

#include "AbilitySystem/XenAbilitySystemComponent.h"
#include "AbilitySystem/XenAttributeSet.h"
#include "Player/XenPlayerController.h"
#include "Player/XenPlayerState.h"

void UXenWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController = WidgetControllerParams.PlayerController;
	PlayerState = WidgetControllerParams.PlayerState;
	AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
	AttributeSet = WidgetControllerParams.AttributeSet;
	
	XenPlayerController = Cast<AXenPlayerController>(PlayerController);
	XenPlayerState = Cast<AXenPlayerState>(PlayerState);
	XenAbilitySystemComponent = Cast<UXenAbilitySystemComponent>(AbilitySystemComponent);
	XenAttributeSet = Cast<UXenAttributeSet>(AttributeSet);
}
