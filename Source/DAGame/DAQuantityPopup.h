// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAWidget.h"
#include "DAQuantityPopup.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuantityConfirmAction, int, Quantity);

/**
 * 
 */
UCLASS()
class DAGAME_API UDAQuantityPopup : public UDAWidget
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(BlueprintReadWrite)
	int CurrentQuantity;

	UPROPERTY(BlueprintReadWrite)
	int MaxQuantity;

	UFUNCTION(BlueprintCallable)
	void SetMaxQuantity(int Quantity);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDisplay();

	UFUNCTION(BlueprintCallable)
	virtual void Accept() override;

	UFUNCTION(BlueprintCallable)
	void IncreaseQuantity();

	UFUNCTION(BlueprintCallable)
	void DecreaseQuantity();

	UFUNCTION(BlueprintCallable)
	virtual void NavigateRight() override;

	UFUNCTION(BlueprintCallable)
	virtual void NavigateLeft() override;

	UPROPERTY(BlueprintAssignable)
	FQuantityConfirmAction ConfirmAction;

protected:
	UPROPERTY(BlueprintReadWrite)
	class UDAIncrementButton* Button;
	
};
