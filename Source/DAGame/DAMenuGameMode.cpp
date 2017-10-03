// Fill out your copyright notice in the Description page of Project Settings.

#include "DAMenuGameMode.h"
#include "DAMasterSettings.h"
#include "DAGameInstance.h"
#include "Kismet/GameplayStatics.h"


ADAMenuGameMode::ADAMenuGameMode()
{

}

void ADAMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameInstance* Inst = UGameplayStatics::GetGameInstance(GetWorld());
	if (Inst) {
		UDAGameInstance* GI = Cast<UDAGameInstance>(Inst);
		if (GI) {
			GI->InitSettings();
		}
	}

	AddMenu(MainWidgetClass);
}

void ADAMenuGameMode::StartButton()
{
	AcceptCurrent();
}

bool ADAMenuGameMode::HasSaveGame()
{
	UGameInstance* Inst = UGameplayStatics::GetGameInstance(GetWorld());
	if (Inst) {
		UDAGameInstance* GI = Cast<UDAGameInstance>(Inst);
		if (GI) {
			const UDAMasterSettings* Settings = GI->GetSettings();
			if (Settings) {
				return Settings->bHasCharacter;
			}
		}
	}

	return false;
}