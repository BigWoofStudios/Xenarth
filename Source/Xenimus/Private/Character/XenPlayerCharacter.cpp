// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/XenPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Player/XenPlayerState.h"

AXenPlayerCharacter::AXenPlayerCharacter()
{
}

void AXenPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}

void AXenPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

void AXenPlayerCharacter::InitAbilityActorInfo()
{
	AXenPlayerState* XenPlayerState = GetPlayerState<AXenPlayerState>();
	checkf(XenPlayerState, TEXT("AXenPlayerCharacter::PossessedBy: PlayerState is not of type AXenPlayerState"));
	XenPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(XenPlayerState, this);
	
	AbilitySystemComponent = XenPlayerState->GetAbilitySystemComponent();
	AttributeSet = XenPlayerState->GetAttributeSet();
}
