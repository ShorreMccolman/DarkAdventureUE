// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DAInventorySystem.h"
#include "DAInventoryScrollbox.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDAInventoryScrollbox : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable)
	void DistributeItemArrays(TArray<FDAInventoryItemDataPair> Items, class UDAInventoryWidget* Menu);

	UFUNCTION(BlueprintImplementableEvent)
	void SetupRowWithItems(const TArray<FDAInventoryItemDataPair>& Items);

protected:
	UPROPERTY(BlueprintReadWrite)
	class UDAInventoryWidget* OwningWidget;

	UPROPERTY()
	TArray<FDAInventoryItemDataPair> CurrentItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UDAItemButton*> Buttons;
	
};
