// Fill out your copyright notice in the Description page of Project Settings.

#include "DAConsumableBase.h"
#include "TimerManager.h"

// Sets default values
ADAConsumableBase::ADAConsumableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Progress = 0.f;
}

// Called when the game starts or when spawned
void ADAConsumableBase::BeginPlay()
{
	Super::BeginPlay();
	
	OnActivate();
	GetWorldTimerManager().SetTimer(LifetimeHandle, this, &ADAConsumableBase::Activate, TimeStep, DoesRepeat);
}

void ADAConsumableBase::Activate()
{
	OnTimer();

	Progress += 0.01f;
	if (Progress >= Duration) {
		OnFinish();
		GetWorldTimerManager().ClearTimer(LifetimeHandle);
		this->Destroy();
	}
}

void ADAConsumableBase::SetDAOwner(class ADACharacter* Character)
{
	DAOwner = Character;
}

