// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AssassinGearSolidGameMode.h"
#include "AssassinGearSolidHUD.h"
#include "AssassinGearSolidCharacter.h"
#include "FPSPlayerController.h"
#include "FPSGameState.h"
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

	GameStateClass = AFPSGameState::StaticClass();
}

void AAssassinGearSolidGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)
	{
		if (SpectatingViewpointClass)
		{
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

			// Change view target if any valid actor has been found
			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActors[0];

                for (FConstPlayerControllerIterator It = GetWorld() -> GetPlayerControllerIterator(); It; It++)
                {
                    APlayerController*PC = It -> Get();
                    if (PC) // call on all the player controllers
                    {
                        PC -> SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
                    }
                }
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr. Please update GameMode class with valid subclass. Cannot change spectating view target!"));
		return;
	}

	AFPSGameState* GS =	GetGameState<AFPSGameState>();

	if (GS)
	{
		GS -> MulticastOnMissionComplete(InstigatorPawn, bMissionSuccess);
	}

	OnMissionCompleted(InstigatorPawn, bMissionSuccess);
}
