// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DAPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UDAPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	
public:

	UFUNCTION()
	void ResetCharacter();

	UFUNCTION()
	void KillCharacter();

	UFUNCTION()
	void QuickDeath();

	UFUNCTION()
	void DamageCharacter();

	UPROPERTY(BlueprintReadWrite)
	FString NextAnimation;

	UPROPERTY(BlueprintReadWrite)
	FString CurrentAnimation;

	UFUNCTION()
	void SetupNextAnimationUnique(FString AnimationName);

	UFUNCTION()
	void SetupNextAnimation(FString AnimationName, bool ShouldOverride);

	UFUNCTION()
	void SetIsLockedOn(bool Locked);

	UPROPERTY(BlueprintReadWrite)
	bool IsLocked;

	UPROPERTY(BlueprintReadWrite)
	bool IsDead;
	

	UPROPERTY(BlueprintReadWrite)
	float Speed;

	UPROPERTY(BlueprintReadWrite)
	float StrafeSpeed;

	UPROPERTY(BlueprintReadWrite)
	float LockedStrafeSpeed;

	UPROPERTY(BlueprintReadWrite)
	float ApproachSpeed;

	UPROPERTY(BlueprintReadWrite)
	float LockedApproachSpeed;

protected:
	UPROPERTY(BlueprintReadWrite)
	class ADACharacter* Character;

	UFUNCTION(BlueprintCallable)
	void ActivateAction();

	UFUNCTION(BlueprintCallable)
	void ExecuteAction();

	UFUNCTION(BlueprintCallable)
	void CompleteAction();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayDamageMontage();
	
};
