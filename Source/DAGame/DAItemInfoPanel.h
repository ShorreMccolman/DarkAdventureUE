// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	void SetupWithItem(class UDAItem* Item);
	
	
};
