#include "XenBlueprintFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Player/XenPlayerState.h"
#include "UI/WidgetController/XenWidgetController.h"

// void UXenBlueprintFunctionLibrary::LoadGameFeaturePlugin(const FString& PluginName, FGameFeaturePluginChangeStateCompleteBP CompleteDelegate)
// {
// 	// Bind the internal static callback
// 	FGameFeaturePluginChangeStateComplete InternalCompleteDelegate;
// 	InternalCompleteDelegate.BindStatic(&UXenBlueprintFunctionLibrary::OnGameFeaturePluginLoadComplete, CompleteDelegate);
//
// 	// Call the LoadGameFeaturePlugin function with the bound delegate
// 	UGameFeaturesSubsystem::Get().LoadGameFeaturePlugin(PluginName, InternalCompleteDelegate);
// }
//
// void UXenBlueprintFunctionLibrary::LoadGameFeaturePlugins(const TArray<FString>& PluginNames,
// 	FGameFeaturePluginChangeStateCompleteBP CompleteDelegate)
// {
// 	FMultipleGameFeaturePluginsLoaded InternalCompleteDelegate;
// 	InternalCompleteDelegate.BindStatic(&UXenBlueprintFunctionLibrary::OnGameFeaturePluginsLoadComplete, CompleteDelegate);
// 	
// 	UGameFeaturesSubsystem::Get().LoadGameFeaturePlugin(PluginNames, FGameFeatureProtocolOptions(), InternalCompleteDelegate);
// }

class AXenPlayerState;

bool UXenBlueprintFunctionLibrary::MakeWidgetControllerParams(const UObject* WorldContextObject,
                                                              FWidgetControllerParams& OutWidgetControllerParamsParams, AXenHUD*& OutXenHUD)
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		OutXenHUD = Cast<AXenHUD>(PlayerController->GetHUD());
		if (OutXenHUD)
		{
			AXenPlayerState* PlayerState = PlayerController->GetPlayerState<AXenPlayerState>();
			UAbilitySystemComponent* AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();
			UAttributeSet* AttributeSet = PlayerState->GetAttributeSet();

			OutWidgetControllerParamsParams.AttributeSet = AttributeSet;
			OutWidgetControllerParamsParams.AbilitySystemComponent = AbilitySystemComponent;
			OutWidgetControllerParamsParams.PlayerState = PlayerState;
			OutWidgetControllerParamsParams.PlayerController = PlayerController;
			return true;
		}
	}
	return false;
}

UOverlayWidgetController* UXenBlueprintFunctionLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WidgetControllerParams;
	AXenHUD* XenHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WidgetControllerParams, XenHUD))
	{
		return XenHUD->GetOverlayWidgetController(WidgetControllerParams);
	}
	
	return nullptr;
}

// void UXenBlueprintFunctionLibrary::OnGameFeaturePluginLoadComplete(const UE::GameFeatures::FResult& Result, FGameFeaturePluginChangeStateCompleteBP CompleteDelegate)
// {
// 	// Execute the Blueprint delegate
// 	CompleteDelegate.ExecuteIfBound(!Result.HasError());
// }
//
// void UXenBlueprintFunctionLibrary::OnGameFeaturePluginsLoadComplete(const TMap<FString, UE::GameFeatures::FResult>& Result, FGameFeaturePluginChangeStateCompleteBP CompleteDelegate)
// {
// 	// Execute the Blueprint delegate
// 	// TODO: How to inform on failure?
// 	CompleteDelegate.ExecuteIfBound(false);
// }
