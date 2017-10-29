// Fill out your copyright notice in the Description page of Project Settings.

#include "DAInteractable.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "DAPlayer.h"

ADAInteractable::ADAInteractable()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(Mesh);
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
	if (Player && OtherComp->ComponentHasTag("Character")) {
		Player->SetCurrentInteractable(this);
		Activate();
	}
}

void ADAInteractable::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ADAPlayer* Player = Cast<ADAPlayer>(OtherActor);
	if (Player && OtherComp->ComponentHasTag("Character")) {
		Player->SetCurrentInteractable(nullptr);
		Deactivate();
	}
}

void ADAInteractable::Activate()
{
	Mesh->SetRenderCustomDepth(true);
}

void ADAInteractable::Deactivate()
{
	Mesh->SetRenderCustomDepth(false);
}

void ADAInteractable::Interact()
{

}