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

	UPROPERTY(BlueprintReadWrite)
	FString NextAnimation;

	UPROPERTY(BlueprintReadWrite)
	FString CurrentAnimation;

	UPROPERTY(BlueprintReadWrite)
	bool IsActive;

	UPROPERTY(BlueprintReadWrite)
	bool FreezeRotation;

	UFUNCTION()
	void SetupNextAnimationUnique(FString AnimationName);

	UFUNCTION()
	void SetupNextAnimation(FString AnimationName, bool ShouldOverride);

	UPROPERTY(BlueprintReadWrite)
	float Speed;

	UFUNCTION()
	void SetIsLockedOn(bool Locked);

	UPROPERTY(BlueprintReadWrite)
	bool IsLocked;

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
	
};
