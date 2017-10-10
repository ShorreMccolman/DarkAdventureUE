// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DACharacterAttributes.h"
#include "DAInventorySystem.h"
#include "DAEquipmentAttributePanel.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDAEquipmentAttributePanel : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void InitAttributesAndInventory(FDACharacterAttributes PlayerAttributes, FDACharacterInventory PlayerInventory);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDACharacterAttributes Attributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDACharacterInventory Inventory;
	
};
