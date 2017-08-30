// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DAPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API ADAPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

protected:
	UPROPERTY()
	class ADAPlayer* DACharacter;

	UPROPERTY()
	bool HoldingRun;

	UPROPERTY()
	int RunBuffer;

	UPROPERTY()
	bool IsLocked;

private:
	UFUNCTION()
	void PressRun();

	UFUNCTION()
	void ReleaseRun();

	UFUNCTION()
	void PressAttack();

	UFUNCTION()
	void PressStrongAttack();

	UFUNCTION()
	void PressTest();

	UFUNCTION()
	void PressLock();
};
