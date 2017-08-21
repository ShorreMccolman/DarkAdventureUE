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
	virtual void Tick(float DeltaTime) override;
	
};
