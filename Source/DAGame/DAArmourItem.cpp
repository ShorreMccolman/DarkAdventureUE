// Fill out your copyright notice in the Description page of Project Settings.

#include "DAArmourItem.h"


UDAArmourItem::UDAArmourItem()
{
	ItemType = EDAItemType::DAItemType_Armour;
}

void UDAArmourItem::ModifyDefensesWithAttributes(float& Defense, float& FireResist, float& ColdResist, float& ElectricResist, const FDACharacterAttributes Attributes) const
{
	Defense += PhysicalDefense + Attributes.HealthStat / 5.f;
	FireResist += FireResistance + Attributes.SpiritualStat / 10.f;
	ColdResist += ColdResistance + Attributes.PracticalStat / 10.f;
	ElectricResist += ElectricResistance + Attributes.ScientificStat / 10.f;
}


