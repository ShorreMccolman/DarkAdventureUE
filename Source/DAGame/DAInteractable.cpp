// Fill out your copyright notice in the Description page of Project Settings.

#include "DAInteractable.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "DAPlayer.h"

ADAInteractable::ADAInteractable()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Trigger->SetSphereRadius(200.f);
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADAInteractable::BeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ADAInteractable::EndOverlap);
}

// Called when the game starts or when spawned
void ADAInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADAInteractable::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	ADAPlayer* Player = Cast<ADAPlayer>(OtherActor);
	if (Player) {
		Player->SetCurrentInteractable(this);
	}
}

void ADAInteractable::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ADAPlayer* Player = Cast<ADAPlayer>(OtherActor);
	if (Player) {
		Player->SetCurrentInteractable(nullptr);
	}
}

void ADAInteractable::Interact()
{

}