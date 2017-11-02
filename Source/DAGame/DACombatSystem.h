#pragma once

#include "CoreMinimal.h"
#include "DACombatSystem.generated.h"


UENUM(BlueprintType)
enum class EDAAttack : uint8
{
	DAAttack_Normal UMETA(DisplayName = "Normal Attack"),
	DAAttack_Heavy UMETA(DisplayName = "Heavy Attack"),
	DAAttack_Combo1 UMETA(DisplayName = "Basic Combo"),
	DAAttack_Combo2 UMETA(DisplayName = "Special Combo")
};

USTRUCT(BlueprintType)
struct FDAWeaponPayload
{
	GENERATED_BODY()

	FDAWeaponPayload()
	{
		NormalDamage = 0;
		FireDamage = 0;
		ColdDamage = 0;
		ElectricDamage = 0;
	}

	FDAWeaponPayload(int Damage) : NormalDamage(Damage) 
	{
		FireDamage = 0;
		ColdDamage = 0;
		ElectricDamage = 0;
	}

	FDAWeaponPayload(int Damage, int Fire, int Cold, int Electric) : NormalDamage(Damage), FireDamage(Fire), ColdDamage(Cold), ElectricDamage(Electric) 
	{

	}

	UPROPERTY()
	int NormalDamage;

	UPROPERTY()
	int FireDamage;

	UPROPERTY()
	int ColdDamage;

	UPROPERTY()
	int ElectricDamage;
};