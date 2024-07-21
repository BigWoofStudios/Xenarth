#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UI/HUD/XenHUD.h"
#include "XenBlueprintFunctionLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FGameFeaturePluginChangeStateCompleteBP, const bool, bSuccess);

UCLASS(BlueprintType)
class XENARTH_API UXenBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // UFUNCTION(BlueprintCallable, Category = "GameFeatures")
    // static void LoadGameFeaturePlugin(const FString& PluginName, FGameFeaturePluginChangeStateCompleteBP CompleteDelegate);
    //
    // UFUNCTION(BlueprintCallable, Category = "GameFeatures")
    // static void LoadGameFeaturePlugins(const TArray<FString>& PluginNames, FGameFeaturePluginChangeStateCompleteBP CompleteDelegate);

    static bool MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWidgetControllerParamsParams, AXenHUD*& OutXenHUD);

    UFUNCTION(BlueprintPure, Category = "UI")
    static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

private:
//     static void OnGameFeaturePluginLoadComplete(const UE::GameFeatures::FResult& Result, FGameFeaturePluginChangeStateCompleteBP CompleteDelegate);
//     static void OnGameFeaturePluginsLoadComplete(const TMap<FString, UE::GameFeatures::FResult>& Result, FGameFeaturePluginChangeStateCompleteBP CompleteDelegate);
};
