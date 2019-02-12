// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectiveActor.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "AssassinGearSolidCharacter.h"

// Sets default values
AObjectiveActor::AObjectiveActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    SphereComp -> SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComp -> SetCollisionResponseToAllChannels(ECR_Ignore);
    SphereComp -> SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    SphereComp -> SetupAttachment(MeshComp);

	SetReplicates(true);
}

// Called when the game starts or when spawned
void AObjectiveActor::BeginPlay()
{
	Super::BeginPlay();

	PlayEffects();
	
}

void AObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(
				this,
				PickupFX,
				GetActorLocation()
			);
}

void AObjectiveActor::NotifyActorBeginOverlap(AActor *OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();

	if (Role == ROLE_Authority)
	{
		// check if overlapped with character
		AAssassinGearSolidCharacter* MyCharacter = Cast<AAssassinGearSolidCharacter>(OtherActor);
		if (MyCharacter)
		{
			MyCharacter -> bIsCarryingObjective = true;

			Destroy();
		}
	}
}

