// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DASelectable.h"
#include "DAIncrementButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIncrementAction, bool, Forward);

/**
 * 
 */
UCLASS()
class DAGAME_API UDAIncrementButton : public UUserWidget, public IDASelectable
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

	UPROPERTY(BlueprintAssignable)
	FIncrementAction IncrementAction;

protected:
	UPROPERTY(BlueprintReadWrite)
	class UDAButton* Button;

	UPROPERTY(BlueprintReadWrite)
	class UTextBlock* Text;

};
