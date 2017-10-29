// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPickup.h"
#include "DAPlayer.h"
#include "Kismet/GameplayStatics.h"

void ADAPickup::Interact()
{
	ADAPlayer* Player = Cast<ADAPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player) {
		Player->AddItemsToInventory(ItemDropID, DropQuantity);
	}

	OpenPickupPopupEvent();
	Destroy();
}

void ADAPickup::SetupWithLootDrop(FDALootDrop Drop)
{
	ItemDropID = Drop.ItemID;
	DropQuantity = Drop.Quantity;
}
