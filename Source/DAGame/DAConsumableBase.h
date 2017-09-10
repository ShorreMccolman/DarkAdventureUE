// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DAConsumableBase.generated.h"

UCLASS()
class DAGAME_API ADAConsumableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADAConsumableBase();

	UFUNCTION()
	void Activate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DoesRepeat;

	UPROPERTY(BlueprintReadWrite)
	float CurrentFill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TargetFill;

	UPROPERTY()
	FTimerHandle LifetimeHandle;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnActivate();

};
