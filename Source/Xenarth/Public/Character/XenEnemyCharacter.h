// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/XenCharacterBase.h"
#include "XenEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class Xenarth_API AXenEnemyCharacter : public AXenCharacterBase
{
	GENERATED_BODY()
public:
	AXenEnemyCharacter();

protected:
	virtual void BeginPlay() override;
};
