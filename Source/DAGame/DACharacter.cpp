// Fill out your copyright notice in the Description page of Project Settings.

#include "DACharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DAPlayerAnimInstance.h"
#include "DAWeaponBase.h"


// Sets default values
ADACharacter::ADACharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ADACharacter::BeginPlay()
{
	Super::BeginPlay();

	USkeletalMeshComponent* Mesh = GetMesh();
	if (Mesh) {
		Animation = Cast<UDAPlayerAnimInstance>(Mesh->GetAnimInstance());
	}

	IsDead = false;
	
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
	Running = ShouldRun;
}

void ADACharacter::GetHit(float Damage)
{
	if (!TakingDamage) {
		IncomingDamage = Damage;
		TakingDamage = true;
		if (Animation) {
			Animation->ShouldImpact = true;
		}
	}
}

void ADACharacter::TriggerIncomingDamage()
{
	Attributes.CurHealth -= IncomingDamage;
	IncomingDamage = 0;
	TakingDamage = false;

	if (Attributes.CurHealth <= 0.f && Animation) {
		IsDead = true;
		Animation->ShouldDie = true;
	}
}

void ADACharacter::TryAttack()
{
	if (Animation && Attributes.CurStamina > 1.f) {
		Animation->ShouldAttack = true;
	}
}

void ADACharacter::TryRoll()
{
	if (Animation && Attributes.CurStamina > 1.f) {
		Animation->ShouldRoll = true;
	}
}

void ADACharacter::ToggleLock()
{
	Locked = !Locked;

	if (!TargetEnemy) {
		Locked = false;
	}

	if (Animation) {
		Animation->IsLocked = Locked;
	}
}

float ADACharacter::GetCurrentHealthPercent() const
{
	return Attributes.CurHealth / Attributes.MaxHealth;
}

float ADACharacter::GetCurrentStaminaPercent() const
{
	return Attributes.CurStamina / Attributes.MaxStamina;
}

void ADACharacter::ConsumeStamina(float Amount)
{
	Attributes.CurStamina = FMath::Max(0.f, Attributes.CurStamina - Amount);
	StaminaBuffer = 2.f;
}

void ADACharacter::StandardMotion(float DeltaTime)
{
	float speedModifier = 1.f;

	if (Running) {
		speedModifier *= 5.f / 3.f;
	}

	float max = WalkSpeed * speedModifier * InputDirection.SizeSquared();
	if (InputDirection.SizeSquared() > 0.0f) {
		TargetDirection = InputDirection;
		TargetDirection.Normalize();
		Speed += Acceleration * DeltaTime;

		// Using this to ease into lower max speed when releasing run
		if (Speed > max) {
			Speed -= Decceleration * DeltaTime;
		}
	}
	else {
		Speed -= Decceleration * DeltaTime;
		Speed = FMath::Max(Speed, 0.f);
	}

	FVector FacingVect = GetActorForwardVector();
	float angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TargetDirection, FacingVect)));
	FVector Cross = FVector::CrossProduct(TargetDirection, FacingVect);

	if (angle > 1.f && InputDirection.SizeSquared() > 0.0f) {
		if (Cross.Z < 0)
			AddControllerYawInput(TurnRate * DeltaTime);
		else
			AddControllerYawInput(-TurnRate * DeltaTime);
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

	FVector FacingVect = GetActorForwardVector();
	float angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TargetDirection, FacingVect)));
	FVector Cross = FVector::CrossProduct(TargetDirection, FacingVect);

	if (angle > 1.f) {
		if (Cross.Z < 0)
			AddControllerYawInput(TurnRate * DeltaTime);
		else
			AddControllerYawInput(-TurnRate * DeltaTime);
	}
}

float ADACharacter::InterpolateSpeed(float Current, float Target, float Acceleration, float DeltaTime)
{
	if (Target == 0.f && FMath::Abs(Current) < 0.1f)
		Current = 0.f;
	else if (Current > Target)
		Current -= Acceleration * DeltaTime;
	else if (Current < Target)
		Current += Acceleration * DeltaTime;

	return Current;
}