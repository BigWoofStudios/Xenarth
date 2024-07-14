#include "XenBlueprintFunctionLibrary.h"

#include "GameFeaturePluginOperationResult.h"
#include "GameFeaturesSubsystem.h"

void UXenBlueprintFunctionLibrary::LoadGameFeaturePlugin(const FString& PluginName, FGameFeaturePluginChangeStateCompleteBP CompleteDelegate)
{
	// Bind the internal static callback
	FGameFeaturePluginChangeStateComplete InternalCompleteDelegate;
	InternalCompleteDelegate.BindStatic(&UXenBlueprintFunctionLibrary::OnGameFeaturePluginLoadComplete, CompleteDelegate);

	// Call the LoadGameFeaturePlugin function with the bound delegate
	UGameFeaturesSubsystem::Get().LoadGameFeaturePlugin(PluginName, InternalCompleteDelegate);
}

void UXenBlueprintFunctionLibrary::LoadGameFeaturePlugins(const TArray<FString>& PluginNames,
	FGameFeaturePluginChangeStateCompleteBP CompleteDelegate)
{
	FMultipleGameFeaturePluginsLoaded InternalCompleteDelegate;
	InternalCompleteDelegate.BindStatic(&UXenBlueprintFunctionLibrary::OnGameFeaturePluginsLoadComplete, CompleteDelegate);
	
	UGameFeaturesSubsystem::Get().LoadGameFeaturePlugin(PluginNames, FGameFeatureProtocolOptions(), InternalCompleteDelegate);
}

void UXenBlueprintFunctionLibrary::OnGameFeaturePluginLoadComplete(const UE::GameFeatures::FResult& Result, FGameFeaturePluginChangeStateCompleteBP CompleteDelegate)
{
	// Execute the Blueprint delegate
	CompleteDelegate.ExecuteIfBound(!Result.HasError());
}

void UXenBlueprintFunctionLibrary::OnGameFeaturePluginsLoadComplete(const TMap<FString, UE::GameFeatures::FResult>& Result, FGameFeaturePluginChangeStateCompleteBP CompleteDelegate)
{
	// Execute the Blueprint delegate
	// TODO: How to inform on failure?
	CompleteDelegate.ExecuteIfBound(false);
}
