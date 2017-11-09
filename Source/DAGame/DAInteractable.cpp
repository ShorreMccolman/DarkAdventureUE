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
}

// Called when the game starts or when spawned
void ADAInteractable::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADAInteractable::InteractableBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ADAInteractable::InteractableEndOverlap);
}

FString ADAInteractable::GetInteractionText_Implementation()
{
	return InteractText;
}

void ADAInteractable::InteractableBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	ADAPlayer* Player = Cast<ADAPlayer>(OtherActor);
	if (Player && OtherComp->ComponentHasTag("Character")) {
		Player->AddPotentialInteractable(this);
		Mesh->SetRenderCustomDepth(true);
	}
}

void ADAInteractable::InteractableEndOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ADAPlayer* Player = Cast<ADAPlayer>(OtherActor);
	if (Player && OtherComp->ComponentHasTag("Character")) {
		Player->RemovePotentialInteractable(this);
		Mesh->SetRenderCustomDepth(false);
	}
}

void ADAInteractable::Interact_Implementation()
{

}