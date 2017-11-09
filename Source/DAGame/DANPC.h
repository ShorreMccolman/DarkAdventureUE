// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DACharacter.h"
#include "DAInteractableInterface.h"
#include "DANPC.generated.h"

/**
 * 
 */
UCLASS()
class DAGAME_API ADANPC : public ADACharacter, public IDAInteractableInterface
{
	GENERATED_BODY()
	
public:
	ADANPC();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact();
	virtual void Interact_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FString GetInteractionText();
	virtual FString GetInteractionText_Implementation() override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InteractableBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	virtual void InteractableBeginOverlap_Implementation(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InteractableEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void InteractableEndOverlap_Implementation(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* Trigger;
};
