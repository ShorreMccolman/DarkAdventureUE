// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayerAnimInstance.h"
#include "DAPlayer.h"

void UDAPlayerAnimInstance::SetupNextAnimation(FString AnimationName)
{
	NextAnimation = AnimationName;
}

void UDAPlayerAnimInstance::ActivateAction()
{
	CurrentAnimation = NextAnimation;
	IsActive = true;
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
}

