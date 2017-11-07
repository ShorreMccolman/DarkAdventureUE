// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DASelectable.h"
#include "DACharacterProfileButton.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API UDACharacterProfileButton : public UUserWidget, public IDASelectable
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDAPlayerProfile* CharacterProfile;

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
	class UButton* Button;
	
};
