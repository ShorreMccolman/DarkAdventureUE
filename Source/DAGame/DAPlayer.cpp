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
#include "DAMainGameMode.h"
#include "DAGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "DAGeneratedAttributes.h"
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
	UDAGameInstance* Instance = Cast<UDAGameInstance>(GetGameInstance());
	if (Instance) {
		PlayerSave = Instance->LoadCurrentPlayerSave();
	}

	if (!PlayerSave) {
		UE_LOG(LogTemp, Warning, TEXT("LoadPlayer - Failed To load character save"));
		return;
	}

	if (PlayerSave->bIsNewPlayer && PlayerStart) {
		PlayerSave->Position = PlayerStart->GetActorLocation();
		PlayerSave->Facing = PlayerStart->GetActorRotation();
		PlayerSave->HomePosition = PlayerStart->GetActorLocation();
	}

	Attributes = PlayerSave->Attributes;
	Inventory = PlayerSave->Inventory;
	Vitals = PlayerSave->Vitals;
	SetActorRotation(PlayerSave->Facing);
	TargetDirection = GetActorForwardVector();
	SetActorLocation(PlayerSave->Position);
	Origin = PlayerSave->HomePosition;

	GeneratedAttributes = NewObject<UDAGeneratedAttributes>(UDAGeneratedAttributes::StaticClass());
	RegenerateAttributes();

	ADAMainGameMode* Mode = Cast<ADAMainGameMode>(GetWorld()->GetAuthGameMode());
	if (Mode) {
		EquipWeaponItem(Inventory.GetItemDataPairInSlot(*Mode->GetItemManager(), EDAEquipmentSlot::EDAEquipmentSlot_RightHand), "RightHand");
		Mode->SetupHUD(this);
	}
}

void ADAPlayer::SavePlayer()
{
	UDAGameInstance* Instance = Cast<UDAGameInstance>(GetGameInstance());
	if (Instance) {
		if (!PlayerSave) {
			PlayerSave = Instance->LoadCurrentPlayerSave();
			if (!PlayerSave) {
				UE_LOG(LogTemp, Warning, TEXT("SavePlayer - Failed To load character save"));
				return;
			}
		}

		Instance->UpdateCurrentPlayerLevel(Attributes.GetLevel());
	}

	PlayerSave->Attributes = Attributes;
	PlayerSave->Inventory = Inventory;
	PlayerSave->Vitals = Vitals;
	PlayerSave->Position = GetActorLocation();
	PlayerSave->Facing = GetActorRotation();
	PlayerSave->HomePosition = Origin;
	PlayerSave->bIsNewPlayer = false;

	UGameplayStatics::SaveGameToSlot(PlayerSave, PlayerSave->ID, 0);
}

// Called when the game starts or when spawned
void ADAPlayer::BeginPlay()
{
	Super::BeginPlay();

	LoadPlayer();
}

// Called every frame
void ADAPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDead)
		return;

	if (bIsTargetLocked && !bIsRunning) {
		if (Animation) {
			Animation->SetIsLockedOn(true);
		}
		LockedMotion(DeltaTime);
	} 
	else {
		if (Animation) {
			Animation->SetIsLockedOn(false);
		}
		StandardMotion(DeltaTime);
	}
}

void ADAPlayer::ChangeRestState(bool IsResting)
{
	if (Animation) {
		Animation->SetupNextAnimation(IsResting ? "Rest" : "Stand", false);
	}
}

void ADAPlayer::Reset()
{
	Super::Reset();
	SavePlayer();
}

void ADAPlayer::AddItemsToInventory(FName ItemID, int Quantity)
{
	ADAMainGameMode* Mode = Cast<ADAMainGameMode>(GetWorld()->GetAuthGameMode());
	UDAItemManager* IM = Mode->GetItemManager();
	if (IM) {
		FDAInventoryItemDataPair Pair = Inventory.GetItemDataPairInSlot(*IM, EDAEquipmentSlot::EDAEquipmentSlot_Consumable1);
		FString InstID = Inventory.AddItem(ItemID, IM, Quantity);
		if (Pair.Item.Quantity == 0 && Pair.Item.ID == ItemID) {
			Inventory.EquipItem(ItemID, InstID,EDAEquipmentSlot::EDAEquipmentSlot_Consumable1);
		}

		Mode->RefreshHUD();
	}
}

void ADAPlayer::TryInteract()
{
	if(CurrentInteractable)
		CurrentInteractable->Interact();
}

void ADAPlayer::AddPotentialInteractable(ADAInteractable* Interactable)
{
	PotentialInteractables.AddUnique(Interactable);
	if (PotentialInteractables.Num() == 1) {
		SetCurrentInteractable(Interactable);
	}
}

void ADAPlayer::RemovePotentialInteractable(ADAInteractable* Interactable)
{
	PotentialInteractables.Remove(Interactable);
	if (CurrentInteractable == Interactable) 
	{
		if (PotentialInteractables.Num() > 0) 
		{
			SetCurrentInteractable(PotentialInteractables[0]);
		}
		else {
			SetCurrentInteractable(nullptr);
		}
	}
}

void ADAPlayer::SetCurrentInteractable(ADAInteractable* Interactable)
{
	CurrentInteractable = Interactable;

	ADAMainGameMode* Mode = Cast<ADAMainGameMode>(GetWorld()->GetAuthGameMode());
	if (Mode) {
		Mode->RefreshHUD();
	}
}

void ADAPlayer::RotateCameraBoom(const float Magnitude)
{
	FRotator Rotation = CameraBoom->GetComponentRotation();
	Rotation.Yaw = Rotation.Yaw + Magnitude;

	CameraBoom->SetWorldRotation(Rotation);
}

void ADAPlayer::ZoomCameraBoom(const float Magnitude)
{
	float Zoom = CameraBoom->TargetArmLength + Magnitude;

	CameraBoom->TargetArmLength = FMath::Clamp(Zoom, 600.f, 1200.f);
}