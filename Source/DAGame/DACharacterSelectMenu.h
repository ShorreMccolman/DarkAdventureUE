// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAWidget.h"
#include "DACharacterSelectMenu.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDACharacterSelectMenu : public UDAWidget
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

	UFUNCTION(BlueprintCallable)
	void LoadCharacterProfiles();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UDAPlayerProfile*> CharacterProfiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UDACharacterProfileButton*> CharacterButtons;

	UPROPERTY()
	int CurrentIndex;
	
};
