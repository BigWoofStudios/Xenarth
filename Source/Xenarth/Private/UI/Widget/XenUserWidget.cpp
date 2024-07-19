// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "UI/Widget/XenUserWidget.h"

void UXenUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
