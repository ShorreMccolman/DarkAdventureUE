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
	float Speed;

	UPROPERTY(BlueprintReadWrite)
	bool ShouldRoll;

	UPROPERTY(BlueprintReadWrite)
	float BlendValue;

protected:
	UPROPERTY(BlueprintReadWrite)
	class ADAPlayer* Player;
	
};
