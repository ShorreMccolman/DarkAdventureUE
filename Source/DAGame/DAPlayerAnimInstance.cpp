// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayerAnimInstance.h"
#include "DAPlayer.h"

void UDAPlayerAnimInstance::ExecuteAction()
{
	ShouldRoll = false;
	ShouldAttack = false;
	ShouldImpact = false;

	LockedStrafeSpeed = StrafeSpeed;
	LockedApproachSpeed = ApproachSpeed;
}

void UDAPlayerAnimInstance::CompleteAction()
{
	ShouldRoll = false;

}

