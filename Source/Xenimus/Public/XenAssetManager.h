// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "XenAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class XENIMUS_API UXenAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UXenAssetManager& Get();
protected:
	virtual void StartInitialLoading() override;
};
