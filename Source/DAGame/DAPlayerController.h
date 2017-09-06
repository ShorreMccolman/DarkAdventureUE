// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DAPlayerController.generated.h"

UENUM(BlueprintType)
enum class EDAInputDirection : uint8
{
	DAInputDirection_Up UMETA(DisplayName = "Up"),
	DAInputDirection_Right UMETA(DisplayName = "Right"),
	DAInputDirection_Down UMETA(DisplayName = "Down"),
	DAInputDirection_Left UMETA(DisplayName = "Left")
};

UENUM(BlueprintType)
enum class EDAControlMode : uint8
{
	DAControlMode_Play UMETA(DisplayName="Play"),
	DAControlMode_FullMenu UMETA(DisplayName = "Full Menu"),
	DAControlMode_PlayMenu UMETA(DisplayName = "Play Menu")
};

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

	UFUNCTION()
	void SetDAControlMode(EDAControlMode Mode);

protected:
	UPROPERTY()
	class ADAMainGameMode* GameMode;

	UPROPERTY()
	class ADAPlayer* DACharacter;

	UPROPERTY(EditAnywhere)
	EDAControlMode ControlMode;

	UPROPERTY()
	bool HoldingRun;

	UPROPERTY()
	int RunBuffer;

	UPROPERTY()
	bool IsLocked;

private:
	UFUNCTION()
	void PressStart();

	UFUNCTION()
	void PressInteract();

	UFUNCTION()
	void PressRun();

	UFUNCTION()
	void ReleaseRun();

	UFUNCTION()
	void PressUse();

	UFUNCTION()
	void PressHeal();

	UFUNCTION()
	void PressAttack();

	UFUNCTION()
	void PressStrongAttack();

	UFUNCTION()
	void PressLock();

	UFUNCTION()
	void PressDUp();

	UFUNCTION()
	void PressDRight();

	UFUNCTION()
	void PressDDown();

	UFUNCTION()
	void PressDLeft();

};
