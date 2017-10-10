// Fill out your copyright notice in the Description page of Project Settings.

#include "DAInventoryScrollbox.h"
#include "DAInventoryWidget.h"

void UDAInventoryScrollbox::DistributeItemArrays(TArray<FDAInventoryItemDataPair> Items, UDAInventoryWidget* Owner)
{
	OwningWidget = Owner;

	int Rows = Items.Num() / 4 + 1;
	for (int i = 0; i < Rows; i++) {
		TArray<FDAInventoryItemDataPair> RowItems;
		for (int j = 0; j < 4; j++) {
			int index = i * 4 + j;
			if (index < Items.Num()) {
				RowItems.Add(Items[index]);
			}
		}
		SetupRowWithItems(RowItems);
	}
}


