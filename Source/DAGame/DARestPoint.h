// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DAInteractable.h"
#include "DARestPoint.generated.h"

UCLASS()
class ADARestPoint : public ADAInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADARestPoint();

	UFUNCTION()
	virtual void Interact() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
