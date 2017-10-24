// Fill out your copyright notice in the Description page of Project Settings.

#include "DAWeaponItem.h"


UDAWeaponItem::UDAWeaponItem()
{
	ItemType = EDAItemType::DAItemType_Weapon;
}

void UDAWeaponItem::ModifyDamageWithAttributes(float& Damage, FDACharacterAttributes Attributes)
{
	Damage += LightAttackPower + Attributes.DamageStat * ScalingFactorModifier(DamageScaling);
	Damage += Attributes.PracticalStat * ScalingFactorModifier(PracticalScaling);
	Damage += Attributes.ScientificStat * ScalingFactorModifier(ScienceScaling);
	Damage += Attributes.SpiritualStat * ScalingFactorModifier(SpiritScaling);
}

