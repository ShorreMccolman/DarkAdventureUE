// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayerProfile.h"
#include "Engine/Texture2D.h"


UTexture2D* UDAPlayerProfile::GetIcon() const
{
	FString Path = FString("/Game/Textures/");
	switch (Worldview)
	{
	case EDAWorldview::DAWorldView_Spritual:
		Path.Append("Spirit");
		break;
	case EDAWorldview::DAWorldView_Practical:
		Path.Append("Real");
		break;
	case EDAWorldview::DAWorldView_Scientific:
		Path.Append("Science");
		break;
	default:
		break;
	}

	switch (Motive)
	{
	case EDAMotive::DAMotive_Duty:
		Path.Append("Duty");
		break;
	case EDAMotive::DAMotive_Glory:
		Path.Append("Glory");
		break;
	case EDAMotive::DAMotive_Profit:
		Path.Append("Profit");
		break;
	case EDAMotive::DAMotive_Power:
		Path.Append("Power");
		break;
	default:
		break;
	}

	return Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *Path));
}