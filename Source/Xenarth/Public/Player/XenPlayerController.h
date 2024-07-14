// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "InputMappingContext.h"
#include "Components/SplineComponent.h"
#include "GameFramework/PlayerController.h"
#include "XenPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class XENARTH_API AXenPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AXenPlayerController();
	virtual void PlayerTick(const float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UAbilitySystemComponent* GetAbilitySystemComponent();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<UInputMappingContext> XenInputMappingContext = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	
#pragma region Movement
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction = nullptr;
	
	void MoveStarted();
	void MoveTriggered();
	void MoveReleased(const FInputActionInstance& ActionData);
	
	void AutoRun();

	FHitResult CursorHit;
	FVector CachedDestination = FVector::ZeroVector;
	FDelegateHandle OnCheckIfCanMove;
	
	UPROPERTY(EditDefaultsOnly, Category=Movement) float ShortPressThreshold = 0.5f;
	UPROPERTY(EditDefaultsOnly, Category=Movement) float AutoRunAcceptanceRadius = 20.f;
	UPROPERTY(VisibleAnywhere, Category=Movement) TObjectPtr<USplineComponent> MovementSpline = nullptr;
	UPROPERTY(VisibleAnywhere, Category=Movement) bool bAutoRunning = false;
	UPROPERTY(VisibleAnywhere, Replicated, Category=Movement) bool bCanMove = true;
	UPROPERTY(VisibleAnywhere, Category=Movement) FGameplayTagContainer BlockMovementTags = FGameplayTagContainer();
#pragma endregion
};
