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
	UFUNCTION()
	virtual void Interact() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OpenMessagePopupEvent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Message;
	
};
