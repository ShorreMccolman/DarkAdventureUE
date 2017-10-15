// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAWidget.h"
#include "Components/TextBlock.h"
#include "DAConfirmPopup.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPopupConfirmAction);

/**
 * 
 */
UCLASS()
class DAGAME_API UDAConfirmPopup : public UDAWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* MainText;

	UPROPERTY(BlueprintAssignable)
	FPopupConfirmAction ConfirmAction;

	UFUNCTION(BlueprintCallable)
	void DoConfirmation();
	
};
