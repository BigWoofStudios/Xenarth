// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/XenCharacterBase.h"

// Sets default values
AXenCharacterBase::AXenCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AXenCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXenCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AXenCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

