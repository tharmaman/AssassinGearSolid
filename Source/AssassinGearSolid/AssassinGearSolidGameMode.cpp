// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AssassinGearSolidGameMode.h"
#include "AssassinGearSolidHUD.h"
#include "AssassinGearSolidCharacter.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AAssassinGearSolidGameMode::AAssassinGearSolidGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/FirstPersonCharacter_BP"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AAssassinGearSolidHUD::StaticClass();
}

void AAssassinGearSolidGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)
	{
		InstigatorPawn -> DisableInput(nullptr);

		if (SpectatingViewpointClass)
		{
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

			// Change viewtarget if any valid actor has been found
			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActors[0];

				APlayerController* PC = Cast<APlayerController>(InstigatorPawn -> GetController());

				if (PC)
				{
					PC -> SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr. Please update GameMode class with valid subclass. Cannot change spectating view target!"));
		return;
	}

	OnMissionCompleted(InstigatorPawn, bMissionSuccess);
}
