// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/XenPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/XenAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/XenPlayerController.h"
#include "Player/XenPlayerState.h"
#include "UI/HUD/XenHUD.h"

AXenPlayerCharacter::AXenPlayerCharacter()
{
	// Align player character mesh with forward direction and capsule component
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bDoCollisionTest = false;
	SpringArm->TargetArmLength = 850.f;
	SpringArm->SetWorldRotation(FRotator(-60.0f, 0.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AXenPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo(); // Init on server
}

void AXenPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo(); // Init on client
}

void AXenPlayerCharacter::InitAbilityActorInfo()
{
	AXenPlayerState* XenPlayerState = GetPlayerState<AXenPlayerState>();
	checkf(XenPlayerState, TEXT("AXenPlayerCharacter::PossessedBy: PlayerState is not of type AXenPlayerState"));
	// Informs the ASC of the Actor that it is bound to, which is the player character in this case 
	XenPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(XenPlayerState, this);
	AbilitySystemComponent = XenPlayerState->GetAbilitySystemComponent();
	AttributeSet = XenPlayerState->GetAttributeSet();

	Cast<UXenAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	// TODO: OnAscRegistered.Broadcast(AbilitySystemComponent);

	// TODO: InitializeDefaultAttributes from saved progress in a function called LoadProgress called in PossessedBy
	if (HasAuthority())
	{
		InitializeDefaultAttributes();		
	}
	
	if (AXenPlayerController* XenPlayerController = Cast<AXenPlayerController>(GetController()))
	{
		if (AXenHUD* XenHUD = Cast<AXenHUD>(XenPlayerController->GetHUD()))
		{
			XenHUD->InitializeOverlay(XenPlayerController, XenPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
