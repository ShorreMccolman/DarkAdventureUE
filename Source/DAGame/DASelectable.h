// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DASelectable.generated.h"

/**
 * 
 */
UINTERFACE(BlueprintType)
class UDASelectable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IDASelectable
{
	GENERATED_IINTERFACE_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Highlight();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UnHighlight();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnSelect();
};
