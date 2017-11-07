// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPickup.h"
#include "DAPlayer.h"
#include "DAMainGameMode.h"
#include "Kismet/GameplayStatics.h"

ADAPickup::ADAPickup()
{
	FGuid guid = FGuid::NewGuid();
	InstanceID = guid.ToString();
	IsInstance = false;
}

void ADAPickup::Init(FName RegionID, bool IsCollected)
{
	if (IsCollected) {
		this->Destroy();
	}
	else {
		IsInstance = true;
		this->RegionID = RegionID;
	}
}

void ADAPickup::Uninit()
{

}

void ADAPickup::Interact()
{
	ADAPlayer* Player = Cast<ADAPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player) {
		Player->AddItemsToInventory(ItemDropID, DropQuantity);
	}

	if (IsInstance) {
		ADAMainGameMode* Mode = Cast<ADAMainGameMode>(GetWorld()->GetAuthGameMode());
		if (Mode) {
			Mode->CollectPickup(RegionID, InstanceID);
		}
	}

	OpenPickupPopupEvent();
	Destroy();
}

void ADAPickup::SetupWithLootDrop(FDALootDrop Drop)
{
	ItemDropID = Drop.ItemID;
	DropQuantity = Drop.Quantity;
}
