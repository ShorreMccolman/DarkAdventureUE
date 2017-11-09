// Fill out your copyright notice in the Description page of Project Settings.

#include "DANPC.h"
#include "DAPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

ADANPC::ADANPC()
{
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(GetMesh());
	Trigger->SetSphereRadius(200.f);
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Called when the game starts or when spawned
void ADANPC::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADANPC::InteractableBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ADANPC::InteractableEndOverlap);
}

FString ADANPC::GetInteractionText_Implementation()
{
	return "Speak";
}

void ADANPC::InteractableBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	ADAPlayer* Player = Cast<ADAPlayer>(OtherActor);
	if (Player && OtherComp->ComponentHasTag("Character")) {
		Player->AddPotentialInteractable(this);
		GetMesh()->SetRenderCustomDepth(true);
	}
}

void ADANPC::InteractableEndOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ADAPlayer* Player = Cast<ADAPlayer>(OtherActor);
	if (Player && OtherComp->ComponentHasTag("Character")) {
		Player->RemovePotentialInteractable(this);
		GetMesh()->SetRenderCustomDepth(false);
	}
}

void ADANPC::Interact_Implementation()
{

}

