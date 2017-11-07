// Fill out your copyright notice in the Description page of Project Settings.

#include "DAItemInfoPanel.h"

void UDAItemInfoPanel::DoItemSetup(FDAInventoryItemDataPair InventoryItem, FDAInventoryItemDataPair CurrentlyEquippedItem)
{
	//SetupWithItem(InventoryItem.Item.Quantity,InventoryItem.Data);
	SetupWithItemPairAndCompare(InventoryItem, CurrentlyEquippedItem);
}

void UDAItemInfoPanel::DoDefaultSetup(EDAItemType ItemType)
{
	SetupWithDefault();
}


