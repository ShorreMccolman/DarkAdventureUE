// Fill out your copyright notice in the Description page of Project Settings.

#include "DAItemManager.h"
#include "DAItem.h"

UDAItemManager::UDAItemManager()
{
	PrimaryComponentTick.bCanEverTick = false;

	FString Path = FString("/Game/Items/ItemDB");
	MasterItemList = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *Path));
}


UDAItem* UDAItemManager::GetItemByID(FName ID) const
{
	if (ID.IsNone()) {
		return nullptr;
	}

	if (!MasterItemList) {
		UE_LOG(LogTemp, Warning, TEXT("Master item list has not been set!!!"))
		return nullptr;
	}

	FDADBItem* DBItem = MasterItemList->FindRow<FDADBItem>(ID, TEXT("LookUp Operation"));
	UDAItem* Item = nullptr;
	if (DBItem) {
		UClass* Class = DBItem->Item.Get();
		if (Class) {
			Item = Cast<UDAItem>(Class->GetDefaultObject());
		}
	}
	return Item;
}
