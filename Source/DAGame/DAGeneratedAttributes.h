// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DAInventorySystem.h"
#include "DAGeneratedAttributes.generated.h"

UCLASS(Blueprintable)
class UDAGeneratedAttributes : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FDACharacterAttributes BaseAttributes;

	UPROPERTY(BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(BlueprintReadWrite)
	float MaxStamina;

	UPROPERTY(BlueprintReadWrite)
	float MainWeaponLightDamage;
	UPROPERTY(BlueprintReadWrite)
	float MainWeaponStrongDamage;

	UPROPERTY(BlueprintReadWrite)
	float OffhandDamage;
	UPROPERTY(BlueprintReadWrite)
	float OffhandDefense;

	UPROPERTY(BlueprintReadWrite)
	float Defense;
	UPROPERTY(BlueprintReadWrite)
	float FireResist;
	UPROPERTY(BlueprintReadWrite)
	float ColdResist;
	UPROPERTY(BlueprintReadWrite)
	float ElectricResist;

	void UpdateWithCharacter(const class ADACharacter& PlayerCharacter);

	void UpdateWithEnemyCharacter(const class ADAEnemy& EnemyCharacter);

private:
	void UpdateAttributesForCharacterSlot(const ADACharacter& PlayerCharacter, EDAEquipmentSlot Slot);
};