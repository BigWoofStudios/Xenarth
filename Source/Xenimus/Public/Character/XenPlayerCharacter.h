// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/XenCharacterBase.h"
#include "XenPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class XENIMUS_API AXenPlayerCharacter : public AXenCharacterBase
{
	GENERATED_BODY()
public:
	AXenPlayerCharacter();
	
	// Called on the server when a player controller is assigned to this character.
	virtual void PossessedBy(AController* NewController) override;
	
	// Called on the client when the player state is replicated.
	virtual void OnRep_PlayerState() override;
	
private:
	void InitAbilityActorInfo();
};
