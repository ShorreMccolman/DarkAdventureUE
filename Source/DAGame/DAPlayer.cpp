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

	Velocity = FVector(1.f, 0.f, 0.f);
	
}

// Called every frame
void ADAPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Find movement direction
	const float ForwardValue = GetInputAxisValue("MoveY");
	const float RightValue = GetInputAxisValue("MoveX");

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	float speedModifier = 1.f;

	// Running Business
	Running = false;
	if (HoldingRun && RunBuffer == 0) {
		Running = true;
	}
	if (RunBuffer > 0)
		RunBuffer--;

	if (Running) {
		speedModifier *= 5.f / 3.f;
	}

	float max = WalkSpeed * speedModifier * MoveDirection.SizeSquared();

	if (MoveDirection.SizeSquared() > 0.0f) {
		Velocity = MoveDirection;
		Velocity.Normalize();
		Facing = Velocity.Rotation();
		Speed += Acceleration * DeltaTime;
		if (Speed > max) {
			Speed -= Decceleration * DeltaTime;
		}

	} else {
		Speed -= Decceleration * DeltaTime;
		Speed = FMath::Max(Speed, 0.f);
	}

	GetCharacterMovement()->MaxWalkSpeed = Speed;

	FVector FacingVect = FVector(FMath::Cos(FMath::DegreesToRadians(GetActorRotation().Yaw)), FMath::Sin(FMath::DegreesToRadians(GetActorRotation().Yaw)), 0.f);
	float angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(Velocity, FacingVect)));
	FVector Cross = FVector::CrossProduct(Velocity, FacingVect);

	if (angle > 1.f && MoveDirection.SizeSquared() > 0.0f) {
		if(Cross.Z < 0)
			AddControllerYawInput(TurnRate * DeltaTime);
		else
			AddControllerYawInput(-TurnRate * DeltaTime);
	}

}

// Called to bind functionality to input
void ADAPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX");
	InputComponent->BindAxis("MoveY");

	InputComponent->BindAction("Run", IE_Pressed, this, &ADAPlayer::PressRun);
	InputComponent->BindAction("Run", IE_Released, this, &ADAPlayer::ReleaseRun);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ADAPlayer::PressAttack);
}

void ADAPlayer::PressAttack()
{
	USkeletalMeshComponent* Mesh = GetMesh();
	if (Mesh) {
		UDAPlayerAnimInstance* Animation = Cast<UDAPlayerAnimInstance>(Mesh->GetAnimInstance());
		if (Animation) {
			Animation->ShouldAttack = true;
		}
	}
}

void ADAPlayer::PressRun()
{
	HoldingRun = true;
	RunBuffer = 30;
}

void ADAPlayer::ReleaseRun()
{
	HoldingRun = false;
	if (RunBuffer > 0) {
		USkeletalMeshComponent* Mesh = GetMesh();
		if (Mesh) {
			UDAPlayerAnimInstance* Animation = Cast<UDAPlayerAnimInstance>(Mesh->GetAnimInstance());
			if (Animation) {
				Animation->ShouldRoll = true;
			}
		}
	}
}

float ADAPlayer::GetCurrentSpeed()
{
	return Speed;
}
