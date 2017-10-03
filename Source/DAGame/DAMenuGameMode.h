// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAGameMode.h"
#include "DAMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ADAMenuGameMode : public ADAGameMode
{
	GENERATED_BODY()
	
public:
	ADAMenuGameMode();

	UFUNCTION()
	virtual void StartButton() override;

	UFUNCTION(BlueprintPure)
	bool HasSaveGame();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<class UUserWidget> MainWidgetClass;
	
};
