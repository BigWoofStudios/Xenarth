// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Player/XenPlayerState.h"

#include "AbilitySystem/XenAbilitySystemComponent.h"
#include "AbilitySystem/XenAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Xenarth/Xenarth.h"

AXenPlayerState::AXenPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UXenAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UXenAttributeSet>(TEXT("AttributeSet"));

	/* Fallback if the variable net update frequency isn't working for some reason */
	NetUpdateFrequency = 100.f;
}

void AXenPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	FDoRepLifetimeParams Parameters;
	
	Parameters.bIsPushBased = true;
	Parameters.RepNotifyCondition = REPNOTIFY_OnChanged;
	
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, CharacterName, Parameters);
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, CharacterLevel, Parameters);
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, CharacterXP, Parameters);
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, AttributePoints, Parameters);
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, SkillPoints, Parameters);
}

void AXenPlayerState::IncreaseCharacterXP_Implementation(const int32 InXP)
{
	CharacterXP += InXP;
	MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, CharacterXP, this);
	
	if (const int32 InCharacterLevel = LevelUpInfo->FindLevelForXP(CharacterXP); InCharacterLevel != CharacterLevel)
	{
		CharacterLevel = InCharacterLevel;
		MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, CharacterLevel, this);
	}
}

void AXenPlayerState::InitializePlayerStateData(const FText& InCharacterName, const int32 InCharacterXP)
{
	if (!HasAuthority())
	{
		UE_LOG(LogXen, Warning, TEXT("Attemping to initialize player state on the client."));
		return;
	}
	
	if (!InCharacterName.EqualTo(CharacterName))
	{
		CharacterName = InCharacterName;
		MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, CharacterName, this);
	}
	
	if (InCharacterXP != CharacterXP)
	{
		CharacterXP = InCharacterXP;
		MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, CharacterXP, this);
	}

	if (const int32 InCharacterLevel = LevelUpInfo->FindLevelForXP(CharacterXP); InCharacterLevel != CharacterLevel)
	{
		CharacterLevel = InCharacterLevel;
		MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, CharacterLevel, this);
	}
}

/* ReplicatedUsing Functions */
void AXenPlayerState::OnRep_AttributePoints(const int32) const { OnAttributePointsChangedDelegate.Broadcast(AttributePoints); }
void AXenPlayerState::OnRep_SkillPoints(const int32) const { OnSkillPointsChangedDelegate.Broadcast(SkillPoints); }
void AXenPlayerState::OnRep_CharacterLevel(const int32) const { OnCharacterLevelChangedDelegate.Broadcast(CharacterLevel, true); }
void AXenPlayerState::OnRep_CharacterXP(const int32) const { OnCharacterXPChangedDelegate.Broadcast(CharacterXP); }
