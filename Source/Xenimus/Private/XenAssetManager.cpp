// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "XenAssetManager.h"

#include "AbilitySystemGlobals.h"

UXenAssetManager& UXenAssetManager::Get()
{
	check(GEngine);
	
	UXenAssetManager* TangiAssetManager = Cast<UXenAssetManager>(GEngine->AssetManager);

	return *TangiAssetManager;
}

void UXenAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	// This is required to use TargetData!
	UAbilitySystemGlobals::Get().InitGlobalData();
}