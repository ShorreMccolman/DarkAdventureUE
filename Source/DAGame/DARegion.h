// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DARegion.generated.h"

UCLASS()
class DAGAME_API ADARegion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADARegion();

	UFUNCTION(BlueprintPure)
	FORCEINLINE FName GetRegionID() const { return RegionID; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FName GetRegionName() const { return RegionDisplayName; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* RegionTrigger;

	UFUNCTION()
	void BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName RegionID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName RegionDisplayName;
	
};
