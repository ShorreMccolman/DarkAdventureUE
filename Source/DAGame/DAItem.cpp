// Fill out your copyright notice in the Description page of Project Settings.

#include "DAItem.h"
#include "DAGeneratedAttributes.h"

float UDAItem::ScalingFactorModifier(EDAScalingFactor Factor)
{
	switch (Factor)
	{
	case EDAScalingFactor::DAScalingFactor_None:
		return 0.f;
	case EDAScalingFactor::DAScalingFactor_A:
		return 1.f;
	case EDAScalingFactor::DAScalingFactor_B:
		return 0.5f;
	case EDAScalingFactor::DAScalingFactor_C:
		return 0.25f;
	case EDAScalingFactor::DAScalingFactor_D:
		return 0.1f;
	}
	return 0.f;
}

void UDAItem::ModifyGeneratedAttributes(UDAGeneratedAttributes& Attributes) const
{

}