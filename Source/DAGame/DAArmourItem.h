// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAItem.h"
#include "DAArmourItem.generated.h"

/**
 * 
 */
UCLASS()
class UDAArmourItem : public UDAItem
{
	GENERATED_BODY()
	
public:
	UDAArmourItem();

	UFUNCTION(BlueprintPure)
		FORCEINLINE FString GetArmourTypeDescription() const {
		switch (ArmourType)
		{
		case EDAArmourType::DAArmourType_Light:
			return "Light Weight";
		case EDAArmourType::DAArmourType_Medium:
			return "Medium Weight";
		case EDAArmourType::DAArmourType_Heavy:
			return "Heavy Weight";
		default:
			return "";
		}
	}

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetPhysicalDefense() const { return PhysicalDefense; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetFireResistance() const { return FireResistance; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetColdResistance() const { return ColdResistance; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetElectricResistance() const { return ElectricResistance; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetRequiredStamina() const { return RequiredStamina; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDAArmourType ArmourType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PhysicalDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int FireResistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ColdResistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ElectricResistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RequiredStamina;
};
