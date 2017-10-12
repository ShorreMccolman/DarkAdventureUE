// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAWidget.h"
#include "DAInventorySystem.h"
#include "DAInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDAInventoryWidget : public UDAWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void NavigateUp() override;

	UFUNCTION(BlueprintCallable)
	virtual void NavigateRight() override;

	UFUNCTION(BlueprintCallable)
	virtual void NavigateDown() override;

	UFUNCTION(BlueprintCallable)
	virtual void NavigateLeft() override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDisplayWithType(EDAItemType ItemType);

	UFUNCTION(BlueprintImplementableEvent)
	void HighlightItemButtonAtRowAndColumn(int Row, int Column);

	UFUNCTION(BlueprintImplementableEvent)
	void RebuildInventoryScrollbox();

	UFUNCTION(BlueprintCallable)
	void InitWithInventoryItems(TArray<FDAInventoryItem> Items);

	UFUNCTION(BlueprintCallable)
	void InitWithItemsAndFilterByType(TArray<FDAInventoryItem> Items, EDAItemType ItemType);

protected:
	UPROPERTY(BlueprintReadWrite)
	int CurrentRow;

	UPROPERTY(BlueprintReadWrite)
	int CurrentColumn;

	UPROPERTY(BlueprintReadWrite)
	bool bIsShowingDescription;

	UPROPERTY(BlueprintReadWrite)
	EDAItemType CurrentItemType;

	UPROPERTY(BlueprintReadWrite)
	EDAItemType CurrentCategory;

	UPROPERTY(BlueprintReadWrite)
	TArray<FDAInventoryItemDataPair> InventoryItems;
	
	UPROPERTY(BlueprintReadWrite)
	class UDAItemInfoPanel* InfoPanel;
};
