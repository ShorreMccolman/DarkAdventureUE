// Fill out your copyright notice in the Description page of Project Settings.

#include "DAWeaponItem.h"
#include "DAGeneratedAttributes.h"

UDAWeaponItem::UDAWeaponItem()
{
	ItemType = EDAItemType::DAItemType_Weapon;
}

void UDAWeaponItem::ModifyGeneratedAttributes(UDAGeneratedAttributes& Attributes) const
{
	Attributes.MainWeaponLightDamage = LightAttackPower + Attributes.BaseAttributes.DamageStat * ScalingFactorModifier(DamageScaling);
	Attributes.MainWeaponLightDamage += Attributes.BaseAttributes.PracticalStat * ScalingFactorModifier(PracticalScaling);
	Attributes.MainWeaponLightDamage += Attributes.BaseAttributes.ScientificStat * ScalingFactorModifier(ScienceScaling);
	Attributes.MainWeaponLightDamage += Attributes.BaseAttributes.SpiritualStat * ScalingFactorModifier(SpiritScaling);

	Attributes.MainWeaponStrongDamage = StrongAttackPower + Attributes.BaseAttributes.DamageStat * ScalingFactorModifier(DamageScaling);
	Attributes.MainWeaponLightDamage += Attributes.BaseAttributes.PracticalStat * ScalingFactorModifier(PracticalScaling);
	Attributes.MainWeaponLightDamage += Attributes.BaseAttributes.ScientificStat * ScalingFactorModifier(ScienceScaling);
	Attributes.MainWeaponLightDamage += Attributes.BaseAttributes.SpiritualStat * ScalingFactorModifier(SpiritScaling);
}

