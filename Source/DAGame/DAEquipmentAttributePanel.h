// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	void InitWithCharacter(class ADACharacter* PlayerCharacter);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDisplay();

protected:
	UPROPERTY(BlueprintReadWrite)
	class UDAGeneratedAttributes* Attributes;
	
};
