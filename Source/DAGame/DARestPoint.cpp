// Fill out your copyright notice in the Description page of Project Settings.

#include "DARestPoint.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "DAMainGameMode.h"
#include "DAPlayer.h"


// Sets default values
ADARestPoint::ADARestPoint()
{

}

// Called when the game starts or when spawned
void ADARestPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADARestPoint::Interact()
{
	ADAMainGameMode* Mode = Cast<ADAMainGameMode>(GetWorld()->GetAuthGameMode());
	if (Mode) {
		Mode->TriggerRestEvent();
	}
}


