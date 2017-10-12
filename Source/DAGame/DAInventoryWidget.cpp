// Fill out your copyright notice in the Description page of Project Settings.

#include "DAInventoryWidget.h"
#include "DAItemManager.h"
#include "DAGameMode.h"
#include "DAItem.h"

void UDAInventoryWidget::InitWithItemsAndFilterByType(TArray<FDAInventoryItem> Items, EDAItemType ItemType)
{
	CurrentCategory = ItemType;
	CurrentRow = 0;
	CurrentColumn = 0;

	InventoryItems.Empty();
	ADAGameMode* Mode = Cast<ADAGameMode>(GetWorld()->GetAuthGameMode());
	UDAItemManager* IM = Mode->GetItemManager();
	if (IM) {
		for (int i = 0; i < Items.Num(); i++) {
			UDAItem* Item = IM->GetItemByID(Items[i].ID);
			if (Item) {
				if (ItemType == EDAItemType::DAItemType_Any || Item->ItemType == ItemType) {
					FDAInventoryItemDataPair Pair = FDAInventoryItemDataPair(Items[i], Item);
					InventoryItems.Add(Pair);
				}
			}
		}

		InventoryItems.Sort([](const FDAInventoryItemDataPair& A, const FDAInventoryItemDataPair& B) {
			return A.Data->DisplayName < B.Data->DisplayName;
		});
	}

	RebuildInventoryScrollbox();
	if (InventoryItems.Num() > 0) {
		HighlightItemButtonAtRowAndColumn(0, 0);
	}
	else {
		UpdateDisplayWithType(ItemType);
	}
}


void UDAInventoryWidget::InitWithInventoryItems(TArray<FDAInventoryItem> Items)
{
	InitWithItemsAndFilterByType(Items, EDAItemType::DAItemType_Any);
}

void UDAInventoryWidget::NavigateUp()
{
	if (CurrentRow > 0) {
		CurrentRow--;
		HighlightItemButtonAtRowAndColumn(CurrentRow, CurrentColumn);
	}
}

void UDAInventoryWidget::NavigateRight()
{
	if (CurrentRow * 4 + CurrentColumn + 1 < InventoryItems.Num()) {
		CurrentColumn++;
		HighlightItemButtonAtRowAndColumn(CurrentRow, CurrentColumn);
	}
}

void UDAInventoryWidget::NavigateDown()
{
	if((CurrentRow + 1) * 4 + CurrentColumn < InventoryItems.Num()) {
		CurrentRow++;
		HighlightItemButtonAtRowAndColumn(CurrentRow, CurrentColumn);
	}
}

void UDAInventoryWidget::NavigateLeft()
{
	if (CurrentColumn > 0) {
		CurrentColumn--;
		HighlightItemButtonAtRowAndColumn(CurrentRow, CurrentColumn);
	}
}
