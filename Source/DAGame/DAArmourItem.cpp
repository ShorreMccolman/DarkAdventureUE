// Fill out your copyright notice in the Description page of Project Settings.

#include "DAArmourItem.h"
#include "DAGeneratedAttributes.h"

UDAArmourItem::UDAArmourItem()
{
	ItemType = EDAItemType::DAItemType_Armour;
}

void UDAArmourItem::ModifyGeneratedAttributes(UDAGeneratedAttributes& Attributes) const
{
	Attributes.Defense += PhysicalDefense + Attributes.BaseAttributes.HealthStat / 5.f;
	Attributes.FireResist += FireResistance + Attributes.BaseAttributes.SpiritualStat / 10.f;
	Attributes.ColdResist += ColdResistance + Attributes.BaseAttributes.PracticalStat / 10.f;
	Attributes.ElectricResist += ElectricResistance + Attributes.BaseAttributes.ScientificStat / 10.f;
}


