// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayerControllerPlay.h"
#include "Components/InputComponent.h"
#include "DAPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "DAMainGameMode.h"

void ADAPlayerControllerPlay::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("TargetX");
	InputComponent->BindAxis("TargetY");

	InputComponent->BindAction("Run", IE_Released, this, &ADAPlayerControllerPlay::ReleaseRun);
	InputComponent->BindAction("Lock", IE_Pressed, this, &ADAPlayerControllerPlay::PressLock);
}

void ADAPlayerControllerPlay::BeginPlay()
{
	Super::BeginPlay();

	DACharacter = Cast<ADAPlayer>(GetPawn());
	CameraBoom = DACharacter->GetCameraBoom();

	SetDAControlMode(EDAControlMode::DAControlMode_Play);
}

float RotVal, PitchVal, ZoomVal;
bool bWasLocked;
void ADAPlayerControllerPlay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool IsLocked = DACharacter->IsTargetLocked();
	if (!bWasLocked && IsLocked) {
		RotVal = CameraBoom->RelativeRotation.Yaw;
		PitchVal = CameraBoom->RelativeRotation.Pitch;
		ZoomVal = CameraBoom->TargetArmLength;
		bWasLocked = IsLocked;
	}
	else if (bWasLocked && !IsLocked) {
		RotVal = 0.f;
		ZoomVal = 0.f;
		bWasLocked = IsLocked;
	}

	if (IsLocked) {
		FVector TargetDirection = DACharacter->GetTargetEnemy()->GetActorLocation() - DACharacter->GetActorLocation();
		TargetDirection.Z = 0.f;
		FRotator TargetRotation = TargetDirection.ToOrientationRotator();

		if (RotVal - TargetRotation.Yaw > 180.f) {
			RotVal -= 360.f;
		}
		else if (TargetRotation.Yaw - RotVal > 180.f) {
			RotVal += 360.f;
		}

		RotVal = FMath::Lerp<float>(RotVal, TargetRotation.Yaw, 5.f * DeltaTime);
		PitchVal = FMath::Lerp<float>(PitchVal, -60.f, 5.f * DeltaTime);
		CameraBoom->SetRelativeRotation(FRotator::MakeFromEuler(FVector(0.f, PitchVal, RotVal)));

		float distance = TargetDirection.Size();
		distance = FMath::Clamp((distance / 200.f - 1.f) * 400.f + 600.f, 600.f, 1200.f);
		ZoomVal = FMath::Lerp<float>(ZoomVal, distance, 2.f * DeltaTime);
		CameraBoom->TargetArmLength = ZoomVal;
	}
	else {
		FRotator Rotation = CameraBoom->GetComponentRotation();
		RotVal = FMath::Lerp<float>(RotVal, GetInputAxisValue("TargetX"), 2.f * DeltaTime);
		Rotation.Yaw = Rotation.Yaw + RotVal;
		PitchVal = FMath::Lerp<float>(PitchVal, (1200.f - CameraBoom->TargetArmLength) / 60.f - 60.f, 10.f * DeltaTime);
		Rotation.Pitch = PitchVal;
		Rotation.Roll = 0.f;
		CameraBoom->SetWorldRotation(Rotation);

		ZoomVal = FMath::Lerp<float>(ZoomVal, GetInputAxisValue("TargetY"), 10.f * DeltaTime);
		float Zoom = CameraBoom->TargetArmLength + ZoomVal * 12.f;
		CameraBoom->TargetArmLength = FMath::Clamp(Zoom, 600.f, 1200.f);
	}

	const float ForwardValue = GetInputAxisValue("MoveY");
	const float RightValue = GetInputAxisValue("MoveX");

	FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f); // Clamped to length 1
	FRotator Rot = FRotator(0.f, CameraBoom->RelativeRotation.Yaw, 0.f);
	MoveDirection = Rot.RotateVector(MoveDirection);

	// Running Business
	bool ShouldRun = false;
	if (HoldingRun && RunBuffer == 0) {
		ShouldRun = true;
	}
	if (RunBuffer > 0)
		RunBuffer--;

	if (DACharacter) {
		if (ShouldRun) {
			DACharacter->ConsumeStamina(8.f * DeltaTime);
			if (DACharacter->GetCurrentStaminaPercent() == 0.f)
				HoldingRun = false;
		}

		DACharacter->SetInputDirection(MoveDirection);
		DACharacter->SetIsRunning(ShouldRun);
	}
}

void ADAPlayerControllerPlay::PressLock()
{
	DACharacter->ToggleLock();
}