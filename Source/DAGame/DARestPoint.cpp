// Fill out your copyright notice in the Description page of Project Settings.

#include "DARestPoint.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "DAMainGameMode.h"
#include "DAPlayer.h"


void ADARestPoint::Activate()
{
	Super::Activate();

	Mesh->SetRenderCustomDepth(true);
}

void ADARestPoint::Deactivate()
{
	Super::Deactivate();

	Mesh->SetRenderCustomDepth(false);
}

void ADARestPoint::Interact()
{
	ADAMainGameMode* Mode = Cast<ADAMainGameMode>(GetWorld()->GetAuthGameMode());
	if (Mode) {
		Mode->TriggerRestEvent();
	}
}


