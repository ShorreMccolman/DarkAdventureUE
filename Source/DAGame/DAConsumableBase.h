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

	UFUNCTION()
	void SetDAOwner(class ADACharacter* Character);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Potency;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DoesRepeat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeStep;

	UPROPERTY(BlueprintReadWrite)
	float Progress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;

	UPROPERTY(BlueprintReadWrite)
	class ADACharacter* DAOwner;

	UPROPERTY()
	FTimerHandle LifetimeHandle;

	UFUNCTION(BlueprintImplementableEvent)
	void OnActivate();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnTimer();

	UFUNCTION(BlueprintImplementableEvent)
	void OnFinish();

};
