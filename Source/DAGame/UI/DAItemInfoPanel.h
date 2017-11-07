// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DAInventorySystem.h"
#include "DAItemInfoPanel.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDAItemInfoPanel : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetupWithItem(int Quantity, UDAItem* ItemData);

	UFUNCTION(BlueprintImplementableEvent)
	void SetupWithItemPairAndCompare(FDAInventoryItemDataPair Target, FDAInventoryItemDataPair Current);
	
	UFUNCTION(BlueprintCallable)
	void DoItemSetup(FDAInventoryItemDataPair InventoryItem, FDAInventoryItemDataPair CurrentlyEquippedItem);

	UFUNCTION(BlueprintImplementableEvent)
	void SetupWithDefault();

	UFUNCTION(BlueprintCallable)
	void DoDefaultSetup(EDAItemType ItemType);
	
};
