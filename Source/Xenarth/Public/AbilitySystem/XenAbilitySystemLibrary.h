// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XenAbilitySystemLibrary.generated.h"

/**
 * 
 */
UCLASS()
class XENARTH_API UXenAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="XenAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, const ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* AbilitySystemComponent);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);
};
