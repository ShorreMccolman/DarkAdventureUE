// Fill out your copyright notice in the Description page of Project Settings.

#include "DAConsumableItem.h"


UDAConsumableItem::UDAConsumableItem()
{
	ItemType = EDAItemType::DAItemType_Consumable;
}


bool UDAConsumableItem::ShouldConsume()
{
	return ConsumableType != EDAConsumableType::DAConsumableType_UnlimitedUse;
}

bool UDAConsumableItem::IsMultiUse()
{
	return ConsumableType == EDAConsumableType::DAConsumableType_MultiUse;
}

