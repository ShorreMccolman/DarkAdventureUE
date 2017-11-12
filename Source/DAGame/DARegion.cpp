// Fill out your copyright notice in the Description page of Project Settings.

#include "DARegion.h"
#include "DAMainGameMode.h"
#include "DAPlayer.h"
#include "DAEnemy.h"
#include "DAPickup.h"
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
	
	ADAMainGameMode* Mode = Cast<ADAMainGameMode>(GetWorld()->GetAuthGameMode());
	if (Mode) {
		Mode->AddLoadedRegion(this);
	}
}

void ADARegion::InitRegion()
{
	for (auto Enemy : RegionEnemies) {
		Enemy->Init(RegionID, false);
	}
	for (auto Item : RegionPickups) {
		if(Item)
			Item->Init(RegionID, false);
	}
}

void ADARegion::InitRegion(FDARegionData RegionData)
{
	for (auto Enemy : RegionEnemies) {
		Enemy->Init(RegionID, RegionData.SlainEnemyIds.Contains<FString>(Enemy->GetInstanceID()));
	}
	for (auto Item : RegionPickups) {
		if (Item)
			Item->Init(RegionID, RegionData.CollectedItemIds.Contains<FString>(Item->GetInstanceID()));
	}
}

void ADARegion::UninitRegion()
{
	for (auto Enemy : RegionEnemies) {
		Enemy->Uninit();
	}
	for (auto Item : RegionPickups) {
		if (Item)
			Item->Uninit();
	}
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