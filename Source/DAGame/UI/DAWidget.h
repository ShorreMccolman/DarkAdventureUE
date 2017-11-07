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
	class UWidget* DefaultSelection;

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsMenuOpen() const { return bMenuIsOpen; }

	UFUNCTION(BlueprintCallable)
	virtual void Accept();

	UFUNCTION(BlueprintImplementableEvent)
	void Refocus();

	UFUNCTION(BlueprintImplementableEvent)
	void RightButton();

	UFUNCTION(BlueprintImplementableEvent)
	void LeftButton();

	UFUNCTION(BlueprintImplementableEvent)
	void Switch();

	UFUNCTION(BlueprintImplementableEvent)
	void Delete();

	UFUNCTION(BlueprintImplementableEvent)
	void Cancel();

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
	UFUNCTION(BlueprintCallable)
	void SetHighlight(class UWidget* Widget);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidget* CurrentHighlight;

	UPROPERTY()
	bool bMenuIsOpen;
	
};
