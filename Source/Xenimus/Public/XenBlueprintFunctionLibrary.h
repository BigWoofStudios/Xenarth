#pragma once

#include "CoreMinimal.h"
#include "GameFeaturesSubsystem.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XenBlueprintFunctionLibrary.generated.h"

// Declare the delegate type
DECLARE_DYNAMIC_DELEGATE_OneParam(FGameFeaturePluginChangeStateCompleteBP, const bool, bSuccess);

UCLASS(BlueprintType)
class XENIMUS_API UXenBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "GameFeatures")
    static void LoadGameFeaturePlugin(const FString& PluginName, FGameFeaturePluginChangeStateCompleteBP CompleteDelegate);

    UFUNCTION(BlueprintCallable, Category = "GameFeatures")
    static void LoadGameFeaturePlugins(const TArray<FString>& PluginNames, FGameFeaturePluginChangeStateCompleteBP CompleteDelegate);

private:
    static void OnGameFeaturePluginLoadComplete(const UE::GameFeatures::FResult& Result, FGameFeaturePluginChangeStateCompleteBP CompleteDelegate);
    static void OnGameFeaturePluginsLoadComplete(const TMap<FString, UE::GameFeatures::FResult>& Result, FGameFeaturePluginChangeStateCompleteBP CompleteDelegate);
};
