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
#include "DAPlayerSave.h"
#include "Kismet/GameplayStatics.h"
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

void ADAPlayer::LoadPlayer()
{
	PlayerSave = Cast<UDAPlayerSave>(UGameplayStatics::LoadGameFromSlot("DA_Default", 0));

	if (!PlayerSave) {
		PlayerSave = Cast<UDAPlayerSave>(UGameplayStatics::CreateSaveGameObject(UDAPlayerSave::StaticClass()));
		if (PlayerStart) {
			PlayerSave->Position = PlayerStart->GetActorLocation();
			PlayerSave->Facing = PlayerStart->GetActorForwardVector();
		}
	}
	Attributes = PlayerSave->Attributes;
	Inventory = PlayerSave->Inventory;
	TargetDirection = PlayerSave->Facing;
	SetActorLocation(PlayerSave->Position);

}

void ADAPlayer::SavePlayer()
{
	if(!PlayerSave) {
		PlayerSave = Cast<UDAPlayerSave>(UGameplayStatics::CreateSaveGameObject(UDAPlayerSave::StaticClass()));
	}

	PlayerSave->Attributes = Attributes;
	PlayerSave->Inventory = Inventory;
	PlayerSave->Position = GetActorLocation();
	PlayerSave->Facing = GetActorForwardVector();

	UGameplayStatics::SaveGameToSlot(PlayerSave, "DA_Default", 0);
}

// Called when the game starts or when spawned
void ADAPlayer::BeginPlay()
{
	Super::BeginPlay();

	LoadPlayer();

	TargetDirection = GetActorForwardVector();

	if (PlayerStart) {
		Origin = PlayerStart->GetActorLocation();
	}
	EquipWeapon("Sword", "RightHandSocket");
	//EquipSecondaryWeapon("Shield", "LeftHandShield");
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
	SavePlayer();
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