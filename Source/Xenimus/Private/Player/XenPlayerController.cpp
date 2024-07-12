// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/XenPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Components/SplineComponent.h"
#include "Input/XenInputComponent.h"

AXenPlayerController::AXenPlayerController()
{
	bReplicates = true;
	MovementSpline = CreateDefaultSubobject<USplineComponent>("MovementSpline");
}

void AXenPlayerController::PlayerTick(const float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRun();
}

void AXenPlayerController::BeginPlay()
{
	Super::BeginPlay();
	checkf(XenInputMappingContext, TEXT("XenInputMappingContext is not set in %s"), *GetName());
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(XenInputMappingContext, 0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AXenPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UXenInputComponent* XenInputComponent = CastChecked<UXenInputComponent>(InputComponent);
	XenInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AXenPlayerController::MoveStarted);
	XenInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AXenPlayerController::MoveTriggered);
	XenInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AXenPlayerController::MoveReleased);
	XenInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &AXenPlayerController::MoveReleased);
}

void AXenPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, true, CursorHit);
}

void AXenPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;
	
	const FVector LocationOnSpline = MovementSpline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
	const FVector Direction = MovementSpline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
	ControlledPawn->AddMovementInput(Direction);

	if ((LocationOnSpline - CachedDestination).Length() <= AutoRunAcceptanceRadius)
	{
		bAutoRunning = false;
	}
}

void AXenPlayerController::MoveStarted()
{
	bAutoRunning = false;
	StopMovement();
}

void AXenPlayerController::MoveReleased(const FInputActionInstance& ActionData)
{
	// Must also not have an ability queued... TBD
	if (ActionData.GetElapsedTime() > ShortPressThreshold) return;
	
	const APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;
	
	if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
	{
		MovementSpline->ClearSplinePoints();
		for (const FVector& PointLoc : NavPath->PathPoints)
		{
			MovementSpline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
		}
	
		if (NavPath->PathPoints.Num() > 0)
		{
			CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
			bAutoRunning = true;
		}
	}
}

void AXenPlayerController::MoveTriggered()
{
	if (CursorHit.bBlockingHit) CachedDestination = CursorHit.ImpactPoint;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection);
	}
}

