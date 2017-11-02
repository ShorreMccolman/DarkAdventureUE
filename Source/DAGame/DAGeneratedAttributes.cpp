// Fill out your copyright notice in the Description page of Project Settings.

#include "DAGeneratedAttributes.h"
#include "DAEnemy.h"

void UDAGeneratedAttributes::UpdateWithCharacter(const ADACharacter& PlayerCharacter)
{
	BaseAttributes = PlayerCharacter.GetAttributes();

	MaxHealth = BaseAttributes.GetBaseHealth();
	MaxStamina = BaseAttributes.GetBaseStamina();
	MainWeaponLightDamage = 0.f;
	MainWeaponStrongDamage = 0.f;
	OffhandDamage = 0.f;
	OffhandDefense = 0.f;
	Defense = 10.f;
	FireResist = 0.f;
	ColdResist = 0.f;
	ElectricResist = 0.f;

	UpdateAttributesForCharacterSlot(PlayerCharacter, EDAEquipmentSlot::EDAEquipmentSlot_RightHand);
	UpdateAttributesForCharacterSlot(PlayerCharacter, EDAEquipmentSlot::EDAEquipmentSlot_LeftHand);
	UpdateAttributesForCharacterSlot(PlayerCharacter, EDAEquipmentSlot::EDAEquipmentSlot_ArmourSet);

	UpdateAttributesForCharacterSlot(PlayerCharacter, EDAEquipmentSlot::EDAEquipmentSlot_Ring1);
	UpdateAttributesForCharacterSlot(PlayerCharacter, EDAEquipmentSlot::EDAEquipmentSlot_Ring2);
	UpdateAttributesForCharacterSlot(PlayerCharacter, EDAEquipmentSlot::EDAEquipmentSlot_Ring3);
	UpdateAttributesForCharacterSlot(PlayerCharacter, EDAEquipmentSlot::EDAEquipmentSlot_Ring4);
}

void UDAGeneratedAttributes::UpdateWithEnemyCharacter(const ADAEnemy& EnemyCharacter)
{
	FDAEnemyAttributes Atts = EnemyCharacter.EnemyAttributes;

	MaxHealth = Atts.MaxHealth;
	MaxStamina = Atts.MaxStamina;
	MainWeaponLightDamage = Atts.MainWeaponLightDamage;
	MainWeaponStrongDamage = Atts.MainWeaponStrongDamage;
	OffhandDamage = Atts.OffhandDamage;
	OffhandDefense = Atts.OffhandDefense;
	Defense = Atts.Defense;
	FireResist = Atts.FireResist;
	ColdResist = Atts.ColdResist;
	ElectricResist = Atts.ElectricResist;
}

void UDAGeneratedAttributes::UpdateAttributesForCharacterSlot(const ADACharacter& PlayerCharacter, EDAEquipmentSlot Slot)
{
	UDAItem* Item = PlayerCharacter.GetEquippedItemInSlot(Slot);
	if (Item) {
		Item->ModifyGeneratedAttributes(*this);
	}
}