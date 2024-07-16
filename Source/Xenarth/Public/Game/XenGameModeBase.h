// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/Data/CharacterClassInfo.h"
#include "GameFramework/GameModeBase.h"
#include "XenGameModeBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class XENARTH_API AXenGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
