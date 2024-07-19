// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "XenHUD.generated.h"

class UXenUserWidget;
class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;

/**
 * 
 */
UCLASS()
class XENARTH_API AXenHUD : public AHUD
{
	GENERATED_BODY()
public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);
	
	void InitializeOverlay(APlayerController* PlayerController, APlayerState* PlayerState, UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet);
	
private:
	UPROPERTY()
	TObjectPtr<UXenUserWidget>  OverlayWidget;	
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UXenUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
