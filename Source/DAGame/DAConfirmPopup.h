// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAWidget.h"
#include "Components/TextBlock.h"
#include "DAConfirmPopup.generated.h"

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

	DECLARE_DELEGATE( FConfirmAction )
	FConfirmAction ConfirmAction;

	UFUNCTION(BlueprintCallable)
	void DoConfirmation();
	
};
