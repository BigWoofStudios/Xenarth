// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Player/XenPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "XenGameplayTags.h"
#include "Components/SplineComponent.h"
#include "Input/XenInputComponent.h"
#include "Net/UnrealNetwork.h"
#include "Xenimus/Xenimus.h"

AXenPlayerController::AXenPlayerController()
{
	bReplicates = true;
	MovementSpline = CreateDefaultSubobject<USplineComponent>("MovementSpline");

	// Tags that the ASC can have that will prevent controlled character movement
	BlockMovementTags.AddTagFast(FXenGameplayTags::Status_Attribute_Life_Empty);
	BlockMovementTags.AddTagFast(FXenGameplayTags::Status_Ability_Queued);
}

void AXenPlayerController::PlayerTick(const float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	GetHitResultUnderCursor(ECC_Visibility, true, CursorHit);
	AutoRun();
}

void AXenPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	FDoRepLifetimeParams Parameters;
	
	Parameters.bIsPushBased = true;
	Parameters.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, bCanMove, Parameters);
}

void AXenPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InPawn);

	UE_LOG(LogXen, Verbose, TEXT("Possessing %s with ASC %s"), *InPawn->GetName(), *AbilitySystemComponent->GetName());
	
	if (AbilitySystemComponent)
	{
		OnCheckIfCanMove = AbilitySystemComponent->RegisterGenericGameplayTagEvent().AddLambda([this](const FGameplayTag InTag, int32)
		{
			if (!BlockMovementTags.HasTagExact(InTag)) return;
			
			const bool bNewValue = AbilitySystemComponent->HasAnyMatchingGameplayTags(BlockMovementTags);
			if (bNewValue == bCanMove) return;
			
            bCanMove = bNewValue;
            MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, bCanMove, this);
		});
	}
}

void AXenPlayerController::OnUnPossess()
{
	AbilitySystemComponent = nullptr;
	OnCheckIfCanMove.Reset();
	
	Super::OnUnPossess();
}

UAbilitySystemComponent* AXenPlayerController::GetAbilitySystemComponent()
{
	if (AbilitySystemComponent == nullptr)
	{
		AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	}

	return AbilitySystemComponent;
}

void AXenPlayerController::BeginPlay()
{
	Super::BeginPlay();
	checkf(XenInputMappingContext, TEXT("XenInputMappingContext is not set in %s"), *GetName());
	
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

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(Subsystem, TEXT("Enhanced Input Subsystem is not available in %s"), *GetName());
	Subsystem->AddMappingContext(XenInputMappingContext, 0);
	
	UXenInputComponent* XenInputComponent = CastChecked<UXenInputComponent>(InputComponent);
	XenInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AXenPlayerController::MoveStarted);
	XenInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AXenPlayerController::MoveTriggered);
	XenInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AXenPlayerController::MoveReleased);
	XenInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &AXenPlayerController::MoveReleased);
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
	if (!bCanMove) return;
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
	if (!bCanMove) return;
	if (CursorHit.bBlockingHit) CachedDestination = CursorHit.ImpactPoint;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection);
	}
}

