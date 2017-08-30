// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayerAnimInstance.h"
#include "DAPlayer.h"

void UDAPlayerAnimInstance::DamageCharacter()
{
	PlayDamageMontage();
}

void UDAPlayerAnimInstance::SetupNextAnimationUnique(FString AnimationName)
{
	if (NextAnimation == "" && CurrentAnimation == "")
		NextAnimation = AnimationName;
}

void UDAPlayerAnimInstance::SetupNextAnimation(FString AnimationName, bool ShouldOverride)
{
	if(NextAnimation == "" || ShouldOverride)
		NextAnimation = AnimationName;
}

void UDAPlayerAnimInstance::ActivateAction()
{
	CurrentAnimation = NextAnimation;
	IsActive = true;
	FreezeRotation = false;
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
	IsActive = false;
	FreezeRotation = false;
}

void UDAPlayerAnimInstance::SetIsLockedOn(bool Locked)
{
	IsLocked = Locked;
	FreezeRotation = false;
}

