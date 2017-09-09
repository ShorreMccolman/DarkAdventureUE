// Fill out your copyright notice in the Description page of Project Settings.

#include "DAItemManager.h"
#include "DAItem.h"

UDAItemManager::UDAItemManager()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UDAItemManager::BeginPlay()
{
	Super::BeginPlay();
	
}


UDAItem* UDAItemManager::GetItemByID(FName ID) const
{
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
