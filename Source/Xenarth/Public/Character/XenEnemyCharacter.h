// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/XenCharacterBase.h"
#include "XenEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class XENARTH_API AXenEnemyCharacter : public AXenCharacterBase
{
	GENERATED_BODY()
public:
	AXenEnemyCharacter();

protected:
	virtual void BeginPlay() override;
	
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Defaults")
	int32 CharacterLevel = 1;
};
