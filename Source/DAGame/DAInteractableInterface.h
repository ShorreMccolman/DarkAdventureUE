// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DAInteractableInterface.generated.h"

UINTERFACE(BlueprintType)
class UDAInteractableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class IDAInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FString GetInteractionText();

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InteractableBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InteractableEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
