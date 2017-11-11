// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAPlayerController.h"
#include "DAPlayerControllerPlay.generated.h"

/**
 * 
 */
UCLASS()
class ADAPlayerControllerPlay : public ADAPlayerController
{
	GENERATED_BODY()
	
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

protected:
	UFUNCTION()
	void PressLock();

	UPROPERTY()
	class USpringArmComponent* CameraBoom;
	
};
