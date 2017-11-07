// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "DASelectable.h"
#include "DAButton.generated.h"

/**
 * 
 */
UCLASS()
class UDAButton : public UButton, public IDASelectable
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetDisabled(bool IsDisabled);

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
	UPROPERTY(BlueprintReadWrite)
	bool bIsDisabled;
	
};
