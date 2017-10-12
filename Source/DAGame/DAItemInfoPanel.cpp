// Fill out your copyright notice in the Description page of Project Settings.

#include "DAItemInfoPanel.h"

void UDAItemInfoPanel::DoItemSetup(FDAInventoryItemDataPair InventoryItem)
{
	SetupWithItem(InventoryItem.Item.Quantity,InventoryItem.Data);
}

void UDAItemInfoPanel::DoDefaultSetup(EDAItemType ItemType)
{
	SetupWithDefault();
}


