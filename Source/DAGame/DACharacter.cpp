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
	
}

// Called every frame
void ADACharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

	FVector InputNormalized = InputDirection;
	InputNormalized.Normalize();

	float Approach = FVector::DotProduct(TargetDirection, InputNormalized);
	float Strafe = FVector::CrossProduct(TargetDirection, InputNormalized).Z;

	FVector Movement = FVector(Strafe, Approach, 0.f);
	Movement.Normalize();

	ApproachValue = Movement.Y * 600.f;
	StrafeValue = Movement.X * 600.f;

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

float ADACharacter::GetCurrentSpeed()
{
	return Speed;
}

float ADACharacter::GetStrafeValue()
{
	return StrafeValue;
}

float ADACharacter::GetApproachValue()
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

void ADACharacter::GetHit()
{
	USkeletalMeshComponent* Mesh = GetMesh();
	if (Mesh) {
		UDAPlayerAnimInstance* Animation = Cast<UDAPlayerAnimInstance>(Mesh->GetAnimInstance());
		if (Animation) {
			Animation->ShouldImpact = true;
		}
	}
}

void ADACharacter::TryAttack()
{
	USkeletalMeshComponent* Mesh = GetMesh();
	if (Mesh) {
		UDAPlayerAnimInstance* Animation = Cast<UDAPlayerAnimInstance>(Mesh->GetAnimInstance());
		if (Animation) {
			Animation->ShouldAttack = true;
		}
	}
}

void ADACharacter::TryRoll()
{
	USkeletalMeshComponent* Mesh = GetMesh();
	if (Mesh) {
		UDAPlayerAnimInstance* Animation = Cast<UDAPlayerAnimInstance>(Mesh->GetAnimInstance());
		if (Animation) {
			Animation->ShouldRoll = true;
		}
	}
}

void ADACharacter::ToggleLock()
{
	Locked = !Locked;

	if (!TargetEnemy) {
		Locked = false;
	}

	USkeletalMeshComponent* Mesh = GetMesh();
	if (Mesh) {
		UDAPlayerAnimInstance* Animation = Cast<UDAPlayerAnimInstance>(Mesh->GetAnimInstance());
		if (Animation) {
			Animation->IsLocked = Locked;
		}
	}
}