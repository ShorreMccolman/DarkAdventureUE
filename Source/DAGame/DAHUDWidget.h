// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DAHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDAHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable)
	void UpdateCharacterAndDisplay(class ADACharacter* PlayerCharacter);

	UFUNCTION(BlueprintImplementableEvent)
	void DoDisplayUpdate();
	
	
protected:
	UPROPERTY(BlueprintReadWrite)
	class ADACharacter* Character;
};
