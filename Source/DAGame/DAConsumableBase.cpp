// Fill out your copyright notice in the Description page of Project Settings.

#include "DAConsumableBase.h"
#include "TimerManager.h"

// Sets default values
ADAConsumableBase::ADAConsumableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADAConsumableBase::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentFill = 0.f;
	GetWorldTimerManager().SetTimer(LifetimeHandle, this, &ADAConsumableBase::Activate, 0.1f, DoesRepeat);
}

void ADAConsumableBase::Activate()
{
	OnActivate();

	CurrentFill += 0.1f;
	if (CurrentFill >= TargetFill) {
		GetWorldTimerManager().ClearTimer(LifetimeHandle);
		this->Destroy();
	}
}

