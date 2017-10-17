// Fill out your copyright notice in the Description page of Project Settings.

#include "DAInventoryWidget.h"
#include "DAItemManager.h"
#include "DAGameMode.h"
#include "DAItem.h"


void UDAInventoryWidget::InitWithInventoryAndFilterByType(FDACharacterInventory Inventory, EDAItemType ItemType, bool ShouldResetPosition)
{
	CurrentCategory = ItemType;

	InventoryItems.Empty();
	ADAGameMode* Mode = Cast<ADAGameMode>(GetWorld()->GetAuthGameMode());
	UDAItemManager* IM = Mode->GetItemManager();
	if (IM) {
		for (int i = 0; i < Inventory.Items.Num(); i++) {
			UDAItem* Item = IM->GetItemByID(Inventory.Items[i].ID);
			if (Item) {
				if (ItemType == EDAItemType::DAItemType_Any || Item->ItemType == ItemType) {
					FDAInventoryItemDataPair Pair = FDAInventoryItemDataPair(Inventory.Items[i], Item);
					Pair.bIsEquipped = Inventory.Equipment.InstanceIDIsEquipped(Inventory.Items[i].InstanceID);
					InventoryItems.Add(Pair);
				}
			}
		}

		InventoryItems.Sort([](const FDAInventoryItemDataPair& A, const FDAInventoryItemDataPair& B) {

			if (A.Item.ID.IsEqual(B.Item.ID)) {

				if (A.bIsEquipped && !B.bIsEquipped)
					return true;
				else if (B.bIsEquipped && !A.bIsEquipped)
					return false;

				return A.Item.InstanceID < B.Item.InstanceID;
			}

			return A.Data->DisplayName < B.Data->DisplayName;
		});
	}

	if (ShouldResetPosition) {
		CurrentRow = 0;
		CurrentColumn = 0;
	}
	else if (CurrentRow * 4 + CurrentColumn + 1 > InventoryItems.Num()) {
		CurrentRow = FMath::CeilToInt(InventoryItems.Num() / 4.f) - 1;
		CurrentColumn = (InventoryItems.Num() - 1) % 4;
	}

	RebuildInventoryScrollbox();
	if (InventoryItems.Num() > 0) {
		HighlightItemButtonAtRowAndColumn(CurrentRow, CurrentColumn);
	}
	else {
		UpdateDisplayWithType(ItemType);
	}
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
		if (CurrentColumn == 3) {
			CurrentColumn = 0;
			CurrentRow++;
		} else {
			CurrentColumn++;
		}

		HighlightItemButtonAtRowAndColumn(CurrentRow, CurrentColumn);
	}
}

void UDAInventoryWidget::NavigateDown()
{
	if((CurrentRow + 1) * 4 + CurrentColumn < InventoryItems.Num()) {
		CurrentRow++;
		HighlightItemButtonAtRowAndColumn(CurrentRow, CurrentColumn);
	}
	else {
		CurrentRow = FMath::CeilToInt(InventoryItems.Num() / 4.f) - 1;
		CurrentColumn = (InventoryItems.Num() - 1) % 4;
		HighlightItemButtonAtRowAndColumn(CurrentRow, CurrentColumn);
	}
}

void UDAInventoryWidget::NavigateLeft()
{
	if (CurrentRow * 4 + CurrentColumn > 0) {
		if (CurrentColumn == 0) {
			CurrentColumn = 3;
			CurrentRow--;
		} else {
			CurrentColumn--;
		}

		HighlightItemButtonAtRowAndColumn(CurrentRow, CurrentColumn);
	}
}
