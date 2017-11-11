// Fill out your copyright notice in the Description page of Project Settings.

#include "DAWeaponBase.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DACharacter.h"
#include "Animation/AnimInstance.h"

ADAWeaponBase::ADAWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerCollider"));
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ADAWeaponBase::TriggerEnter);
	BoxCollider->SetupAttachment(Mesh);
}

void ADAWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	DisableCollision();
}

void ADAWeaponBase::SetDAOwner(class ADACharacter* TheOwner)
{
	DAOwner = TheOwner;
}

void ADAWeaponBase::DisableCollision()
{
	Payload = FDAWeaponPayload();
	if (BoxCollider) {
		BoxCollider->bGenerateOverlapEvents = false;
	}
}

void ADAWeaponBase::EnableCollision(FDAWeaponPayload NewPayload)
{
	Payload = NewPayload;
	if (BoxCollider) {
		BoxCollider->bGenerateOverlapEvents = true;
	}
}

void ADAWeaponBase::TriggerEnter( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != DAOwner && OtherComp->ComponentHasTag("Character")) {
		ADACharacter* Character = Cast<ADACharacter>(OtherActor);
		if (Character) {
			Character->GetHit(Payload);
		}
	}
}
