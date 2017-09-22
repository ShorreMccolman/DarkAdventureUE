// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayerAnimInstance.h"
#include "DAPlayer.h"

void UDAPlayerAnimInstance::ResetCharacter()
{
	NextAnimation = "";
	CurrentAnimation = "";

	IsDead = false;
	IsLocked = false;

	Speed = 0;
	StrafeSpeed = 0;
	ApproachSpeed = 0;
}

void UDAPlayerAnimInstance::DamageCharacter()
{
	PlayDamageMontage();
}

void UDAPlayerAnimInstance::KillCharacter()
{
	IsDead = true;
	NextAnimation = "Death";
}

void UDAPlayerAnimInstance::SetupNextAnimationUnique(FString AnimationName)
{
	if (NextAnimation == "" && CurrentAnimation == "") {
		NextAnimation = AnimationName;
	}
}

void UDAPlayerAnimInstance::SetupNextAnimation(FString AnimationName, bool ShouldOverride)
{
	if (NextAnimation == "" || ShouldOverride) {
		NextAnimation = AnimationName;
	}
}

void UDAPlayerAnimInstance::ActivateAction()
{
	CurrentAnimation = NextAnimation;
}

void UDAPlayerAnimInstance::ExecuteAction()
{
	NextAnimation = "";

	LockedStrafeSpeed = StrafeSpeed;
	LockedApproachSpeed = ApproachSpeed;
}

void UDAPlayerAnimInstance::CompleteAction()
{
	CurrentAnimation = "";
	Character->SetCharacterRotationLock(false);
}

void UDAPlayerAnimInstance::SetIsLockedOn(bool Locked)
{
	if(Locked != IsLocked)
		Character->SetCharacterRotationLock(false);

	IsLocked = Locked;
}

