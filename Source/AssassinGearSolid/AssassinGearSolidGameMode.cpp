// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AssassinGearSolidGameMode.h"
#include "AssassinGearSolidHUD.h"
#include "AssassinGearSolidCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAssassinGearSolidGameMode::AAssassinGearSolidGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AAssassinGearSolidHUD::StaticClass();
}
