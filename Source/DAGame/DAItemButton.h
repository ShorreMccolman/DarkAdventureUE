// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DASelectable.h"
#include "DAItemButton.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDAItemButton : public UUserWidget, public IDASelectable
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

	UFUNCTION(BlueprintCallable)
	void SetItem(class UDAItem* Item);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDAItem* Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UImage* IconImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UButton* Button;
	
	
};
