// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAItem.h"
#include "DAWeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDAWeaponItem : public UDAItem
{
	GENERATED_BODY()
	
public:
	UDAWeaponItem();

	UFUNCTION(BlueprintPure)
	FORCEINLINE FString GetWeaponTypeDescription() const {
		switch (WeaponType)
		{
		case EDAWeaponType::DAWeaponType_OneHand:
			return "One Handed Weapon";
		case EDAWeaponType::DAWeaponType_TwoHand:
			return "Two Handed Weapon";
		case EDAWeaponType::DAWeaponType_Ranged:
			return "Ranged Weapon";
		default:
			return "";
		}
	}

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetLightAttackPower() const { return LightAttackPower; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetStrongAttackPower() const { return StrongAttackPower; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetDamageRequirement() const { return DamageRequirement; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetScienceRequirement() const { return ScienceRequirement; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetPracticalRequirement() const { return PracticalRequirement; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetSpiritRequirement() const { return SpiritRequirement; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FString GetDescriptionForScaling(EDAScalingFactor Factor) const {
		switch (Factor)
		{
		case EDAScalingFactor::DAScalingFactor_None:
			return "--";
		case EDAScalingFactor::DAScalingFactor_A:
			return "A";
		case EDAScalingFactor::DAScalingFactor_B:
			return "B";
		case EDAScalingFactor::DAScalingFactor_C:
			return "C";
		case EDAScalingFactor::DAScalingFactor_D:
			return "D";
		default:
			return "--";
		}
	}

	UFUNCTION(BlueprintPure)
	FORCEINLINE FString GetDamageScaling() const { return GetDescriptionForScaling(DamageScaling); }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FString GetScienceScaling() const { return GetDescriptionForScaling(ScienceScaling); }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FString GetPracticalScaling() const { return GetDescriptionForScaling(PracticalScaling); }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FString GetSpiritScaling() const { return GetDescriptionForScaling(SpiritScaling); }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDAWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LightAttackPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StrongAttackPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DamageRequirement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ScienceRequirement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PracticalRequirement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SpiritRequirement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDAScalingFactor DamageScaling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDAScalingFactor ScienceScaling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDAScalingFactor PracticalScaling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDAScalingFactor SpiritScaling;
	
};
