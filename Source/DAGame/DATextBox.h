// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DASelectable.h"
#include "DATextBox.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDATextBox : public UUserWidget, public IDASelectable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Highlight();
	virtual void Highlight_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UnHighlight();
	virtual void UnHighlight_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSelect();
	virtual void OnSelect_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBorder* Border;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UEditableTextBox* TextBox;
	
	
};
