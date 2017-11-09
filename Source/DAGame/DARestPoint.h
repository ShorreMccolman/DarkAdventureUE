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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact();
	virtual void Interact_Implementation() override;
	
protected:
	virtual void BeginPlay() override;
};
