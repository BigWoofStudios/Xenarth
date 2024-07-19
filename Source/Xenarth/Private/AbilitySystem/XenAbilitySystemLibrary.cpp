// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "AbilitySystem/XenAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/XenGameplayEffectContext.h"
#include "Game/XenGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UXenAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, const ECharacterClass CharacterClass, const float Level, UAbilitySystemComponent* AbilitySystemComponent)
{
	const AActor* AvatarActor = AbilitySystemComponent->GetAvatarActor();
	
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	
	FGameplayEffectContextHandle PrimaryAttributesContextHandle = AbilitySystemComponent->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
}

UCharacterClassInfo* UXenAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	if (const AXenGameModeBase* XenGameMode = Cast<AXenGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		return XenGameMode->CharacterClassInfo;
	}
	
	return nullptr;
}
