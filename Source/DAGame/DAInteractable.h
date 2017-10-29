// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DAInteractable.generated.h"

UCLASS()
class ADAInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADAInteractable();

	UFUNCTION()
	virtual void Interact();

	UFUNCTION(BlueprintPure)
	FORCEINLINE FString GetInteractText() { return InteractText; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Activate();

	virtual void Deactivate();

	UFUNCTION()
	void BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString InteractText;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* Trigger;

	
};
