#pragma once

#include "CoreMinimal.h"
#include "DACharacterAttributes.h"
#include "DAInventorySystem.h"
#include "DACharacter.h"
#include "DAGeneratedAttributes.generated.h"


USTRUCT(BlueprintType)
struct FDAGeneratedAttributes 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(BlueprintReadWrite)
	float CurHealth;

	UPROPERTY(BlueprintReadWrite)
	float MaxStamina;
	UPROPERTY(BlueprintReadWrite)
	float CurStamina;

	UPROPERTY(BlueprintReadWrite)
	int MaxHeals;

	UPROPERTY(BlueprintReadWrite)
	float WeaponDamage;
	UPROPERTY(BlueprintReadWrite)
	float AlternateWeaponDamage;

	UPROPERTY(BlueprintReadWrite)
	float OffhandDamage;
	UPROPERTY(BlueprintReadWrite)
	float AlternateOffhandDamage;

	UPROPERTY(BlueprintReadWrite)
	float Defense;
	UPROPERTY(BlueprintReadWrite)
	float FireResist;
	UPROPERTY(BlueprintReadWrite)
	float ColdResist;
	UPROPERTY(BlueprintReadWrite)
	float ElectricResist;

	FDAGeneratedAttributes()
	{

	}

	FDAGeneratedAttributes(const ADACharacter& Character)
	{
		FDACharacterAttributes Attributes = Character.GetAttributes();

		CurHealth = Attributes.CurHealth;
		MaxHealth = Attributes.MaxHealth;
		CurStamina = Attributes.CurStamina;
		MaxStamina = Attributes.MaxStamina;

		MaxHeals = Attributes.MaxHeals;

		WeaponDamage = 0.f;
		UDAItem* Main = Character.GetEquippedItemInSlot(EDAEquipmentSlot::EDAEquipmentSlot_RightHand);
		if (Main) {
			UDAWeaponItem* Weapon = Cast<UDAWeaponItem>(Main);
			if (Weapon) {
				Weapon->ModifyDamageWithAttributes(WeaponDamage, Attributes);
			}
		}

		AlternateWeaponDamage = 0.f;
		UDAItem* Alt = Character.GetEquippedItemInSlot(EDAEquipmentSlot::EDAEquipmentSlot_RightHandAlt);
		if (Alt) {
			UDAWeaponItem* Weapon = Cast<UDAWeaponItem>(Alt);
			if (Weapon) {
				Weapon->ModifyDamageWithAttributes(AlternateWeaponDamage, Attributes);
			}
		}

		OffhandDamage = 0.f;
		UDAItem* Off = Character.GetEquippedItemInSlot(EDAEquipmentSlot::EDAEquipmentSlot_LeftHand);
		if (Off) {
			UDAWeaponItem* Weapon = Cast<UDAWeaponItem>(Off);
			if (Weapon) {
				Weapon->ModifyDamageWithAttributes(OffhandDamage, Attributes);
			}
		}

		AlternateOffhandDamage = 0.f;
		UDAItem* OffAlt = Character.GetEquippedItemInSlot(EDAEquipmentSlot::EDAEquipmentSlot_LeftHandAlt);
		if (OffAlt) {
			UDAWeaponItem* Weapon = Cast<UDAWeaponItem>(OffAlt);
			if (Weapon) {
				Weapon->ModifyDamageWithAttributes(AlternateOffhandDamage, Attributes);
			}
		}

		Defense = 0.f;
		FireResist = 0.f;
		ColdResist = 0.f;
		ElectricResist = 0.f;
		UDAItem* ArmourItem = Character.GetEquippedItemInSlot(EDAEquipmentSlot::EDAEquipmentSlot_ArmourSet);
		if (ArmourItem) {
			UDAArmourItem* Armour = Cast<UDAArmourItem>(ArmourItem);
			if (Armour) {
				Armour->ModifyDefensesWithAttributes(Defense, FireResist, ColdResist, ElectricResist, Attributes);
			}
		}
	}
};