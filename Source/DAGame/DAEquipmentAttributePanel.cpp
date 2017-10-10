// Fill out your copyright notice in the Description page of Project Settings.

#include "DAEquipmentAttributePanel.h"


void UDAEquipmentAttributePanel::InitAttributesAndInventory(FDACharacterAttributes PlayerAttributes, FDACharacterInventory PlayerInventory)
{
	Attributes = PlayerAttributes;
	Inventory = PlayerInventory;

}

