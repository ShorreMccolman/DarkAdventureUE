// Fill out your copyright notice in the Description page of Project Settings.

#include "DAOffhandItem.h"
#include "DAGeneratedAttributes.h"

UDAOffhandItem::UDAOffhandItem()
{
	ItemType = EDAItemType::DAItemType_Offhand;
}

void UDAOffhandItem::ModifyGeneratedAttributes(UDAGeneratedAttributes& Attributes) const
{
	Attributes.OffhandDamage += OffensivePower;

	Attributes.OffhandDefense += DefensivePower;
}

