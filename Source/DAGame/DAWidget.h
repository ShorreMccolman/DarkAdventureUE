// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DAPlayerController.h"
#include "DAWidget.generated.h"

/**
 * 
 */
UCLASS()
class UDAWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDAButton* DefaultSelection;

	UFUNCTION(BlueprintCallable)
	virtual void Accept();

	UFUNCTION(BlueprintCallable)
	virtual void Cancel();

	UFUNCTION(BlueprintCallable)
	virtual void OnOpen();

	UFUNCTION(BlueprintCallable)
	virtual void OnClose();

	UFUNCTION(BlueprintCallable)
	virtual void NavigateUp();

	UFUNCTION(BlueprintCallable)
	virtual void NavigateRight();

	UFUNCTION(BlueprintCallable)
	virtual void NavigateDown();

	UFUNCTION(BlueprintCallable)
	virtual void NavigateLeft();


protected:
	UFUNCTION()
	void SetHighlightedButton(class UDAButton* Button);

	UPROPERTY()
	class UDAButton* HighlightedButton;
	
};
