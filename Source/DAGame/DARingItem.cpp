// Fill out your copyright notice in the Description page of Project Settings.

#include "DARingItem.h"
#include "DAGeneratedAttributes.h"

UDARingItem::UDARingItem()
{
	ItemType = EDAItemType::DAItemType_Ring;
}


void UDARingItem::ModifyGeneratedAttributes(UDAGeneratedAttributes& Attributes) const
{
	ModifyAttributesEvent(&Attributes);
}
