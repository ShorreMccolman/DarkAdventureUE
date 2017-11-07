// Fill out your copyright notice in the Description page of Project Settings.

#include "DARestPoint.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DAMainGameMode.h"
#include "DAPlayer.h"


void ADARestPoint::Interact()
{
	ADAMainGameMode* Mode = Cast<ADAMainGameMode>(GetWorld()->GetAuthGameMode());
	if (Mode) {
		Mode->TriggerRestEvent();
	}

	ADAPlayer* Player = Cast<ADAPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player) {
		Player->SnapshotOrigin();
		Player->ChangeRestState(true);
	}
}


