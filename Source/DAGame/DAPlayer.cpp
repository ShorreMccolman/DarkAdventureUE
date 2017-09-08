// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerStart.h"
#include "Components/SkeletalMeshComponent.h"
#include "DAPlayerAnimInstance.h"
#include "DAInteractable.h"
#include "DAWeaponBase.h"

#include "Blueprint/BlueprintSupport.h"


// Sets default values
ADAPlayer::ADAPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WalkSpeed = 600.f;
	Acceleration = 800.f;
	Decceleration = 1200.f;
	TurnRate = 100.f;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void ADAPlayer::BeginPlay()
{
	Super::BeginPlay();

	TargetDirection = GetActorForwardVector();

	if (PlayerStart) {
		Origin = PlayerStart->GetActorLocation();
	}
	EquipWeapon("Blueprint'/Game/Weapons/BP_DA2HWeapon.BP_DA2HWeapon'", "RightHandSocket");
}

// Called every frame
void ADAPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDead)
		return;

	if (Locked && !Running) {
		Animation->SetIsLockedOn(true);
		LockedMotion(DeltaTime);
	} 
	else {
		Animation->SetIsLockedOn(false);
		StandardMotion(DeltaTime);
	}
}

void ADAPlayer::Reset()
{
	Super::Reset();

}

void ADAPlayer::TryInteract()
{
	if(CurrentInteractable)
		CurrentInteractable->Interact();
}

void ADAPlayer::SetCurrentInteractable(ADAInteractable* Interactable)
{
	CurrentInteractable = Interactable;
}