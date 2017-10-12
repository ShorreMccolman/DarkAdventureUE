// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAWidget.h"
#include "DAInventorySystem.h"
#include "DAEquipmentWidget.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDAEquipmentWidget : public UDAWidget
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
	void UpdateItemInfoPanel();

protected:
	UPROPERTY(BlueprintReadWrite)
	bool bIsShowingDescription;

	UPROPERTY(BlueprintReadWrite)
	EDAItemType CurrentItemType;
	
	UPROPERTY(BlueprintReadWrite)
	class UDAItemInfoPanel* InfoPanel;
};
