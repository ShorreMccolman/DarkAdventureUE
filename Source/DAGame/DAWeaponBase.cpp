// Fill out your copyright notice in the Description page of Project Settings.

#include "DAWeaponBase.h"
#include "Components/BoxComponent.h"

// Sets default values
ADAWeaponBase::ADAWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADAWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	DisableCollision();
}

// Called every frame
void ADAWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADAWeaponBase::DisableCollision()
{
	if (BoxCollider) {
		BoxCollider->bGenerateOverlapEvents = false;
	}
}

void ADAWeaponBase::EnableCollision()
{
	if (BoxCollider) {
		BoxCollider->bGenerateOverlapEvents = true;
	}
}
