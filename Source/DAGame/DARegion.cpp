// Fill out your copyright notice in the Description page of Project Settings.

#include "DARegion.h"
#include "DAMainGameMode.h"
#include "DAPlayer.h"
#include "Components/BoxComponent.h"

// Sets default values
ADARegion::ADARegion()
{
	PrimaryActorTick.bCanEverTick = false;

	RegionTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(RegionTrigger);
	RegionTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RegionTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADARegion::BeginOverlap);
	RegionTrigger->OnComponentEndOverlap.AddDynamic(this, &ADARegion::EndOverlap);
}

// Called when the game starts or when spawned
void ADARegion::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADARegion::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	ADAPlayer* Player = Cast<ADAPlayer>(OtherActor);
	if (Player && OtherComp->ComponentHasTag("Character")) {
		ADAMainGameMode* Mode = Cast<ADAMainGameMode>(GetWorld()->GetAuthGameMode());
		if (Mode) {
			Mode->EnterRegion(this);
		}
	}
}

void ADARegion::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ADAPlayer* Player = Cast<ADAPlayer>(OtherActor);
	if (Player && OtherComp->ComponentHasTag("Character")) {
		ADAMainGameMode* Mode = Cast<ADAMainGameMode>(GetWorld()->GetAuthGameMode());
		if (Mode) {
			Mode->LeaveRegion(this);
		}
	}
}