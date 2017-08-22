// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayerAnimInstance.h"


void UDAPlayerAnimInstance::ExecuteAction()
{
	ShouldRoll = false;
	ShouldAttack = false;
	ShouldImpact = false;
}

void UDAPlayerAnimInstance::CompleteAction()
{
	ShouldRoll = false;
}

