// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DAPlayerAnimInstance.h"


// Sets default values
ADAPlayer::ADAPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
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
}

// Called every frame
void ADAPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Locked)
		LockedMotion(DeltaTime);
	else
		StandardMotion(DeltaTime);
}

void ADAPlayer::StandardMotion(float DeltaTime)
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

void ADAPlayer::LockedMotion(float DeltaTime)
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

float ADAPlayer::GetCurrentSpeed()
{
	return Speed;
}

float ADAPlayer::GetStrafeValue()
{
	return StrafeValue;
}

float ADAPlayer::GetApproachValue()
{
	return ApproachValue;
}

void ADAPlayer::ForceCurrentFacing()
{
	FVector Normalized = InputDirection;
	Normalized.Normalize();

	float angle = FMath::RadiansToDegrees(FMath::Acos(Normalized.X));

	FRotator rotation = FRotator(-180.f,0.f, -180.f);
	FaceRotation(rotation);
}

void ADAPlayer::SetInputDirection(FVector Input)
{
	InputDirection = Input;
}

void ADAPlayer::SetIsRunning(bool ShouldRun)
{
	Running = ShouldRun;
}

void ADAPlayer::GetHit()
{
	USkeletalMeshComponent* Mesh = GetMesh();
	if (Mesh) {
		UDAPlayerAnimInstance* Animation = Cast<UDAPlayerAnimInstance>(Mesh->GetAnimInstance());
		if (Animation) {
			Animation->ShouldImpact = true;
		}
	}
}

void ADAPlayer::TryAttack()
{
	USkeletalMeshComponent* Mesh = GetMesh();
	if (Mesh) {
		UDAPlayerAnimInstance* Animation = Cast<UDAPlayerAnimInstance>(Mesh->GetAnimInstance());
		if (Animation) {
			Animation->ShouldAttack = true;
		}
	}
}

void ADAPlayer::TryRoll()
{
	USkeletalMeshComponent* Mesh = GetMesh();
	if (Mesh) {
		UDAPlayerAnimInstance* Animation = Cast<UDAPlayerAnimInstance>(Mesh->GetAnimInstance());
		if (Animation) {
			Animation->ShouldRoll = true;
		}
	}
}

void ADAPlayer::ToggleLock()
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
