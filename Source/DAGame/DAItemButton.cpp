// Fill out your copyright notice in the Description page of Project Settings.

#include "DAItemButton.h"
#include "DAItem.h"
#include "DAWidget.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Text.h"



void UDAItemButton::Highlight_Implementation()
{
	Button->SetBackgroundColor(FLinearColor(1.0f, 0.35f, 0.2f));
}

void UDAItemButton::UnHighlight_Implementation()
{
	Button->SetBackgroundColor(FLinearColor::White);
}

void UDAItemButton::OnSelect_Implementation()
{
	if (ConfirmAction.IsBound()) {
		ConfirmAction.Broadcast(this);
	}
}

void UDAItemButton::SetItem(FDAInventoryItemDataPair Item)
{
	this->Item = Item;

	EquippedIconImage->SetVisibility(Item.bIsEquipped ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

	if (Item.Data) {
		if (Item.Data->MaxQuantity > 0) {
			QuantityText->SetText(FText::AsNumber(Item.Item.Quantity));
		} else {
			QuantityText->SetText(FText::FromString(""));
		}

		IconImage->SetBrushFromTexture(Item.Data->Icon);
	}
}

void UDAItemButton::SetItemTypeAndTexture(EDAItemType Type, UTexture2D* Texture)
{
	Item = FDAInventoryItemDataPair();
	ItemType = Type;

	QuantityText->SetText(FText::FromString(""));
	EquippedIconImage->SetVisibility(ESlateVisibility::Hidden);

	if (Texture) {
		IconImage->SetBrushFromTexture(Texture);
	}
}
