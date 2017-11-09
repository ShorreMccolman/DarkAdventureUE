// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAInteractable.h"
#include "DAMessageTrigger.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API ADAMessageTrigger : public ADAInteractable
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact();
	virtual void Interact_Implementation() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OpenMessagePopupEvent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Message;
	
};
