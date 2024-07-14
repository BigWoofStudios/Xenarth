// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/XenPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/XenPlayerState.h"

AXenPlayerCharacter::AXenPlayerCharacter()
{
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 850.f;
	CameraBoom->SetWorldRotation(FRotator(-60.0f, 0.0f, 0.0f));

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponent");
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
	TopDownCameraComponent->bUsePawnControlRotation = false;
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
	// Init on server
	InitAbilityActorInfo();
}

void AXenPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Init on client
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
