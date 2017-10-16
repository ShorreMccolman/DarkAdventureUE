// Fill out your copyright notice in the Description page of Project Settings.

#include "DACharacter.h"
#include "DAEnemy.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "DAPlayerAnimInstance.h"
#include "DAWeaponBase.h"
#include "AI/Navigation/NavigationSystem.h"
#include "AI/Navigation/NavigationPath.h"
#include "DAGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "DAItemManager.h"
#include "DAItem.h"
#include "DAConsumableItem.h"
#include "DAConsumableBase.h"


// Sets default values
ADACharacter::ADACharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bIsDead = false;
}

// Called when the game starts or when spawned
void ADACharacter::BeginPlay()
{
	Super::BeginPlay();

	ShowTarget(false);

	USkeletalMeshComponent* Mesh = GetMesh();
	if (Mesh) {
		Animation = Cast<UDAPlayerAnimInstance>(Mesh->GetAnimInstance());
	}
}

// Called every frame
void ADACharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (StaminaBuffer <= 0.f) {
		Attributes.RegainStamina(16.f * DeltaTime);
	}
	else {
		StaminaBuffer -= DeltaTime;
	}

}

void ADACharacter::Reset()
{
	bIsDead = false;
	Inventory.Reset();
	Attributes.Reset();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetActorLocation(Origin);

	if (Animation) {
		Animation->ResetCharacter();
	}
}

void ADACharacter::ShowDetails(bool ShouldShow)
{

}

void ADACharacter::OnCharacterDeath()
{
	bIsDead = true;
	Animation->KillCharacter();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ADACharacter::EquipSecondaryWeapon(FName ID, FName SocketName)
{
	if (Weapon2) {
		Weapon2->Destroy();
		Weapon2 = nullptr;
	}

	ADAGameMode* Mode = Cast<ADAGameMode>(GetWorld()->GetAuthGameMode());
	UDAItemManager* IM = Mode->GetItemManager();
	if (IM) {
		UDAItem* Item = IM->GetItemByID(ID);
		if (Item) {
			FVector Location(0.f, 0.f, 0.f);
			FRotator Rotation(0.f, 0.f, 0.f);
			FActorSpawnParameters SpawnInfo;
			Weapon2 = GetWorld()->SpawnActor<ADAWeaponBase>(Item->ObjClass, Location, Rotation, SpawnInfo);
			if (Weapon2) {
				Weapon2->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);
				Weapon2->DisableCollision();
				Weapon2->SetDAOwner(this);
			}
		}
	}
}

void ADACharacter::EquipWeapon(FName ID, FName SocketName)
{
	if (Weapon) {
		Weapon->Destroy();
		Weapon = nullptr;
	}

	ADAGameMode* Mode = Cast<ADAGameMode>(GetWorld()->GetAuthGameMode());
	UDAItemManager* IM = Mode->GetItemManager();
	if (IM) {
		UDAItem* Item = IM->GetItemByID(ID);
		if (Item) {
			FVector Location(0.f, 0.f, 0.f);
			FRotator Rotation(0.f, 0.f, 0.f);
			FActorSpawnParameters SpawnInfo;
			Weapon = GetWorld()->SpawnActor<ADAWeaponBase>(Item->ObjClass, Location, Rotation, SpawnInfo);
			if (Weapon) {
				Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);
				Weapon->DisableCollision();
				Weapon->SetDAOwner(this);
				GetMesh()->SetAnimInstanceClass(Weapon->GetAnimBP());
				Animation = Cast<UDAPlayerAnimInstance>(GetMesh()->GetAnimInstance());
			}
		}
	}
}

void ADACharacter::UseHealItem()
{
	ADAGameMode* Mode = Cast<ADAGameMode>(GetWorld()->GetAuthGameMode());
	UDAItemManager* IM = Mode->GetItemManager();
	if (IM) {
		UDAItem* Item = IM->GetItemByID(Inventory.Heals.ID);
		if (Item) {
			FVector Location(0.f, 0.f, 0.f);
			FRotator Rotation(0.f, 0.f, 0.f);
			FActorSpawnParameters SpawnInfo;
			ADAConsumableBase* Consumable = GetWorld()->SpawnActor<ADAConsumableBase>(Item->ObjClass, Location, Rotation, SpawnInfo);
			Consumable->SetDAOwner(this);
			Inventory.ConsumeHeal();
		}
	}
}

void ADACharacter::UseConsumableItem(FName ID)
{
	ADAGameMode* Mode = Cast<ADAGameMode>(GetWorld()->GetAuthGameMode());
	UDAItemManager* IM = Mode->GetItemManager();
	if (IM) {
		UDAConsumableItem* Item = Cast<UDAConsumableItem>(IM->GetItemByID(ID));
		if (Item) {

			FVector Location(0.f, 0.f, 0.f);
			FRotator Rotation(0.f, 0.f, 0.f);
			FActorSpawnParameters SpawnInfo;
			if (Item->ObjClass) {
				ADAConsumableBase* Consumable = GetWorld()->SpawnActor<ADAConsumableBase>(Item->ObjClass, Location, Rotation, SpawnInfo);
				if (Consumable) {
					Consumable->SetDAOwner(this);
				}
			}
			if (Item->ShouldConsume()) {
				Inventory.RemoveItem(ID);
			}
		}
	}
}

void ADACharacter::FireProjectile()
{
	FVector Location = Weapon->GetActorLocation();
	FRotator Rotation = GetActorRotation();
	FActorSpawnParameters SpawnInfo;
	AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, Location, Rotation, SpawnInfo);
}

float ADACharacter::GetCurrentSpeed() const
{
	return Speed;
}

float ADACharacter::GetStrafeValue() const
{
	return StrafeValue;
}

float ADACharacter::GetApproachValue() const
{
	return ApproachValue;
}

void ADACharacter::SetInputDirection(FVector Input)
{
	InputDirection = Input;
}

void ADACharacter::SetIsRunning(bool ShouldRun)
{
	bIsRunning = ShouldRun;
}

void ADACharacter::SetCharacterRotationLock(bool Lock)
{
	bShouldLockRotation = Lock;
}

void ADACharacter::GetHit(float Damage)
{
	if (!bIsTakingDamage && !bIsDead) {
		IncomingDamage = Damage;
		bIsTakingDamage = true;
		if (Animation) {
			Animation->DamageCharacter();
		}
	}
}

void ADACharacter::TriggerIncomingDamage()
{
	Attributes.CurHealth -= IncomingDamage;
	IncomingDamage = 0;
	bIsTakingDamage = false;

	if (Attributes.CurHealth <= 0.f && Animation) {
		OnCharacterDeath();
	}
}

void ADACharacter::TryAttack()
{
	if (Animation && Attributes.CurStamina > 1.f) {
		Animation->SetupNextAnimation("Attack", false);
	}
}

void ADACharacter::TryStrongAttack()
{
	if (Animation && Attributes.CurStamina > 1.f) {
		Animation->SetupNextAnimation("StrongAttack", false);
	}
}

void ADACharacter::TryHeal()
{
	if (Animation && Inventory.HasHeal()) {
		Animation->SetupNextAnimation("Heal", false);
	}
}

void ADACharacter::TryRoll()
{
	if (Animation && Attributes.CurStamina > 1.f) {
		Animation->SetupNextAnimation("Roll", false);
	}
}

void ADACharacter::ToggleLock()
{
	bool ShouldLock = !bIsTargetLocked;

	if (ShouldLock)
		UpdateBestTarget();

	if (!TargetEnemy) {
		ShouldLock = false;
	}
	
	SetIsLocked(ShouldLock);
}

void ADACharacter::AddPotentialTarget(ADACharacter *Target)
{
	PotentialTargets.Add(Target);
}

void ADACharacter::RemovePotentialTarget(ADACharacter* Target)
{
	PotentialTargets.Remove(Target);
	if (TargetEnemy == Target) {
		TargetEnemy->ShowTarget(false);
		UpdateBestTarget();
	}
}

void ADACharacter::DiscardItemsWithID(FName ID, int Quantity)
{
	if (Quantity > 0) {
		Inventory.RemoveItem(ID, Quantity);
	}
}

void ADACharacter::EquipItemToSlot(FName ID, EDAEquipmentSlot Slot)
{
	Inventory.EquipItem(ID, Slot);
}

void ADACharacter::RemoveItemFromSlot(EDAEquipmentSlot Slot)
{
	Inventory.UnequipItem(Slot);
}

UDAItem* ADACharacter::GetEquippedItemInSlot(EDAEquipmentSlot Slot)
{
	ADAGameMode* Mode = Cast<ADAGameMode>(GetWorld()->GetAuthGameMode());
	UDAItemManager* IM = Mode->GetItemManager();
	UDAItem* Item = nullptr;
	if (IM) {
		Item = Inventory.GetItemInSlot(IM, Slot);
	}

	return Item;
}

FDAInventoryItemDataPair ADACharacter::GetEquippedPairInSlot(EDAEquipmentSlot Slot)
{
	ADAGameMode* Mode = Cast<ADAGameMode>(GetWorld()->GetAuthGameMode());
	UDAItemManager* IM = Mode->GetItemManager();
	if (IM) {
		return Inventory.GetItemDataPairInSlot(*IM, Slot);
	}
	else {
		return FDAInventoryItemDataPair();
	}
}

void ADACharacter::UpdateBestTarget()
{
	if (PotentialTargets.Num() == 0) {
		TargetEnemy = nullptr;
		SetIsLocked(false);
		return;
	}

	FVector Location = GetActorLocation();
	PotentialTargets.Sort([Location](const ADACharacter& A, const ADACharacter& B) {
		return FVector::Distance(A.GetActorLocation(), Location) < FVector::Distance(B.GetActorLocation(), Location);
	});
	TargetEnemy = PotentialTargets[0];
}

float ADACharacter::GetCurrentHealthPercent() const
{
	return Attributes.CurHealth / Attributes.MaxHealth;
}

float ADACharacter::GetCurrentStaminaPercent() const
{
	return Attributes.CurStamina / Attributes.MaxStamina;
}

void ADACharacter::HealCharacter(float Amount)
{
	if (bIsDead)
		return;

	Attributes.AdjustCurrentHealth(Amount);
}

void ADACharacter::ConsumeStamina(float Amount)
{
	Attributes.ConsumeStamina(Amount);
	StaminaBuffer = 2.f;
}

void ADACharacter::FaceTargetDirection(FVector Direction, float angle, float DeltaTime)
{
	if (bShouldLockRotation)
		return;

	FVector Cross = FVector::CrossProduct(Direction, GetActorForwardVector());
	if (angle > 3.f) {
		FVector Vect = GetActorRotation().Euler();
		if (FMath::Abs(Cross.Z) < 0.01f) {

		} else if (Cross.Z < 0)
			Vect += FVector(0.f, 0.f, TurnRate * DeltaTime);
		else
			Vect += FVector(0.f, 0.f, -TurnRate * DeltaTime);


		FRotator Rot = FRotator::MakeFromEuler(Vect);
		SetActorRotation(Rot);
	}

}

void ADACharacter::StandardMotion(float DeltaTime)
{
	float speedModifier = 1.f;
	float inputSquareMagnitude = InputDirection.SizeSquared();

	if (bIsRunning) {
		speedModifier *= 5.f / 3.f;
	}

	float max = WalkSpeed * speedModifier * inputSquareMagnitude;
	if (inputSquareMagnitude > 0.0f) {
		TargetDirection = InputDirection;
		TargetDirection.Normalize();
		Speed = InterpolateSpeed(Speed, max, Acceleration, DeltaTime);
	} else {
		Speed = InterpolateSpeed(Speed, 0.f, Decceleration, DeltaTime);
	}

	if (bIsTargetLocked && Speed < 300.f)
		Speed = 300.f;

	if (Animation)
		Animation->Speed = Speed;

	if (inputSquareMagnitude > 0.f) {
		float angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TargetDirection, GetActorForwardVector())));
		if (angle > 140.f) {
			if (Animation) {
				Animation->SetupNextAnimationUnique("TurnAround");
			}
		}
		FaceTargetDirection(TargetDirection, angle, DeltaTime);
	}
}

void ADACharacter::LockedMotion(float DeltaTime)
{
	Speed = 0.f;
	TargetDirection = TargetEnemy->GetActorLocation() - GetActorLocation();
	TargetDirection.Normalize();

	float Approach = FVector::DotProduct(TargetDirection, InputDirection) * 600.f;
	float Strafe = FVector::CrossProduct(TargetDirection, InputDirection).Z * 600.f;

	ApproachValue = InterpolateSpeed(ApproachValue, Approach, 2000.f, DeltaTime);
	StrafeValue = InterpolateSpeed(StrafeValue, Strafe, 2000.f, DeltaTime);

	if (Animation) {
		Animation->ApproachSpeed = ApproachValue;
		Animation->StrafeSpeed = StrafeValue;
	}

	float angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TargetDirection, GetActorForwardVector())));
	FaceTargetDirection(TargetDirection, angle, 2.f * DeltaTime);
}

void ADACharacter::Pursue(float Distance, float DeltaTime)
{
	UNavigationPath *tpath;
	UNavigationSystem* system = GetWorld()->GetNavigationSystem();
	tpath = system->FindPathToActorSynchronously(GetWorld(), GetActorLocation(), TargetEnemy);

	int Num = tpath->PathPoints.Num();

	FVector Targ;
	if (tpath->PathPoints.Num() > 1)
		Targ = tpath->PathPoints[1];
	else
		Targ = GetActorLocation();

	TargetDirection = Targ - GetActorLocation();
	TargetDirection.Normalize();

	float angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TargetDirection, GetActorForwardVector())));
	FaceTargetDirection(TargetDirection, angle, DeltaTime);

	if (Distance > 150.f) {
		Speed = InterpolateSpeed(Speed, 600.f, Acceleration, DeltaTime);
	} else if (Distance < 140.f) {
		Speed = InterpolateSpeed(Speed, -100.f, Decceleration, DeltaTime);
	} else {
		Speed = InterpolateSpeed(Speed, 0.f, Decceleration, DeltaTime);
	}

	if (Animation)
		Animation->Speed = Speed;
}

void ADACharacter::HoldPosition(float DeltaTime)
{
	Speed = InterpolateSpeed(Speed, 0.f, Decceleration, DeltaTime);

	if (Animation)
		Animation->Speed = Speed;
}

void ADACharacter::SetIsLocked(bool ShouldLock)
{
	bIsTargetLocked = ShouldLock;

	if (TargetEnemy) {
		TargetEnemy->ShowTarget(bIsTargetLocked);
	}

	if (Animation) {
		Animation->SetIsLockedOn(bIsTargetLocked);
	}
}

void ADACharacter::ShowTarget(bool ShouldTarget)
{

}

float ADACharacter::InterpolateSpeed(float Current, float Target, float Acceleration, float DeltaTime)
{
	if (Current < Target + 1.f && Current > Target - 1.f) {
		Current = Target;
	}
	else if (Current > Target)
		Current -= Acceleration * DeltaTime;
	else if (Current < Target)
		Current += Acceleration * DeltaTime;

	return Current;
}