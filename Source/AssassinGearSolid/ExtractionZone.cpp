// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "AssassinGearSolidCharacter.h"
#include "AssassinGearSolidGameMode.h"

// Sets default values
AExtractionZone::AExtractionZone()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp -> SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp -> SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp -> SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp -> SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	OverlapComp -> SetHiddenInGame(false);

	OverlapComp -> OnComponentBeginOverlap.AddDynamic(this, &AExtractionZone::HandleOverlap);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp -> DecalSize = FVector(200.0f, 200.0f, 200.0f);
	DecalComp -> SetupAttachment(RootComponent);
}

void AExtractionZone::HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
									UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
									const FHitResult &SweepResult)
{
    AAssassinGearSolidCharacter* MyPawn = Cast<AAssassinGearSolidCharacter>(OtherActor);
    if (MyPawn == nullptr)
	{
    	return;
	}

	if (MyPawn -> bIsCarryingObjective)
	{
		AAssassinGearSolidGameMode* GM = Cast<AAssassinGearSolidGameMode>(GetWorld() -> GetAuthGameMode());

		if (GM)
		{
			GM -> CompleteMission(MyPawn);
		}
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}
    UE_LOG(LogTemp, Log, TEXT("Overlapped with extraction zone!"));
}

