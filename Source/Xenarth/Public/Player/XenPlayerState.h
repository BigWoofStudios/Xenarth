// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "LevelUpInfo.h"
#include "GameFramework/PlayerState.h"
#include "XenPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCharacterStatChanged, int32 /*StatValue*/)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCharacterLevelChanged, const int32 /*StatValue*/, const bool /*bLevelUp*/)

/**
 * 
 */
UCLASS(Blueprintable)
class XENARTH_API AXenPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AXenPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	UPROPERTY(EditDefaultsOnly, Category="PlayerState Data", meta=(Description="Used to find data based on character XP."))
	TObjectPtr<ULevelUpInfo> LevelUpInfo;
	
	FOnCharacterStatChanged OnCharacterXPChangedDelegate;
	FOnCharacterStatChanged OnAttributePointsChangedDelegate;
	FOnCharacterStatChanged OnSkillPointsChangedDelegate;
	FOnCharacterLevelChanged OnCharacterLevelChangedDelegate;
	
	UFUNCTION(BlueprintGetter, Category="PlayerState Data|Accessors")
	FORCEINLINE FText GetCharacterName() const { return CharacterName; }
	
	UFUNCTION(BlueprintGetter, Category="PlayerState Data|Accessors")
	FORCEINLINE int32 GetCharacterLevel() const { return CharacterLevel; }
	
	UFUNCTION(BlueprintGetter, Category="PlayerState Data|Accessors")
	FORCEINLINE int32 GetCharacterXP() const { return CharacterXP; }
	
	UFUNCTION(BlueprintGetter, Category="PlayerState Data|Accessors")
	FORCEINLINE int32 GetAttributePoints() const { return AttributePoints; }
	
	UFUNCTION(BlueprintGetter, Category="PlayerState Data|Accessors")
	FORCEINLINE int32 GetSkillPoints() const { return SkillPoints; }

	void IncreaseCharacterXP(const int32 InXP);

	/*
	 * Called from the server to initialize the player state's data. This should be used when loading in saved data
	 * from a database or saved game state.
	 */
	void InitializePlayerStateData(const FText& InCharacterName, const int32 InCharacterXP);

protected:
	UPROPERTY(VisibleAnywhere, Category="Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Ability System")
	TObjectPtr<UAttributeSet> AttributeSet;
	
private:
	UPROPERTY(VisibleAnywhere, Replicated) FText CharacterName = FText();

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_AttributePoints, Category="PlayerState Data")
	int32 AttributePoints = 0;
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_SkillPoints, Category="PlayerState Data")
	int32 SkillPoints = 0;
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_CharacterLevel, Category="PlayerState Data")
	int32 CharacterLevel = 1;
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_CharacterXP, Category="PlayerState Data")
	int32 CharacterXP = 0;
	
	UFUNCTION()void OnRep_AttributePoints(const int32 OldValue) const;
	UFUNCTION()void OnRep_SkillPoints(const int32 OldValue) const;
	UFUNCTION()void OnRep_CharacterLevel(const int32 OldValue) const;
	UFUNCTION()void OnRep_CharacterXP(const int32 OldValue) const;
};
