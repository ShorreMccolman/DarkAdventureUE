// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAWidget.h"
#include "DAInventorySystem.h"
#include "DAItemOptionsPopup.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDAItemOptionsPopup : public UDAWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void DoUseAction();

	UFUNCTION(BlueprintCallable)
	void DoDiscardAction();

	UPROPERTY(BlueprintAssignable)
	FItemButtonConfirmAction UseAction;

	UPROPERTY(BlueprintAssignable)
	FItemButtonConfirmAction DiscardAction;

	UPROPERTY(BlueprintReadWrite)
	class UDAItemButton* Button;
	
	
};
