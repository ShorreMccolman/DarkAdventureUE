// Fill out your copyright notice in the Description page of Project Settings.

#include "DALevelStreamer.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DAPlayer.h"

// Sets default values
ADALevelStreamer::ADALevelStreamer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);
	Trigger->OnComponentBeginOverlap.AddUniqueDynamic(this, &ADALevelStreamer::BeginOverlap);
}

// Called when the game starts or when spawned
void ADALevelStreamer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADALevelStreamer::Finished()
{
	
}

void ADALevelStreamer::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (LevelToTrigger.IsNone()) {
		UE_LOG(LogTemp, Warning, TEXT("Forget to set level name for level streamer"))
		return;
	}

	ADAPlayer* Player = Cast<ADAPlayer>(OtherActor);
	if (Player && OtherComp->ComponentHasTag("Character")) {
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		LatentInfo.ExecutionFunction = FName("Finished");
		LatentInfo.Linkage = 0;
		LatentInfo.UUID = 123456;

		if (bShouldLoad) {
			UGameplayStatics::LoadStreamLevel(this, LevelToTrigger, true, true, LatentInfo);
		}
		else {
			UGameplayStatics::UnloadStreamLevel(this, LevelToTrigger, LatentInfo);
		}
	}
}