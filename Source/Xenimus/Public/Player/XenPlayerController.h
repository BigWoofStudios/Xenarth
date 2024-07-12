// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "Components/SplineComponent.h"
#include "GameFramework/PlayerController.h"
#include "XenPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class XENIMUS_API AXenPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AXenPlayerController();
	virtual void PlayerTick(const float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<UInputMappingContext> XenInputMappingContext = nullptr;

	void CursorTrace();
	FHitResult CursorHit;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction = nullptr;
	
	void MoveStarted();
	void MoveTriggered();
	void MoveReleased(const FInputActionInstance& ActionData);

	FVector CachedDestination = FVector::ZeroVector;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;

	UPROPERTY(EditDefaultsOnly, Category=Movement)
	float AutoRunAcceptanceRadius  = 20.f;

	UPROPERTY(VisibleAnywhere, Category=Movement)
	TObjectPtr<USplineComponent> MovementSpline = nullptr;

	void AutoRun();
};
