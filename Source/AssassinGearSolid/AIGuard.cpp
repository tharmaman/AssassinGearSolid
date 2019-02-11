// Fill out your copyright notice in the Description page of Project Settings.

#include "AIGuard.h"
#include "Classes/Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAIGuard::AAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	PawnSensingComp -> OnSeePawn.AddDynamic(this, &AAIGuard::OnPawnSeen);
	PawnSensingComp -> OnHearNoise.AddDynamic(this, &AAIGuard::OnNoiseHeard);
}

// Called when the game starts or when spawned
void AAIGuard::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIGuard::OnPawnSeen(APawn *SeenPawn)
{
	if (SeenPawn == nullptr) return;


	UE_LOG(LogTemp, Warning, TEXT("PAWN SEEN"));
	DrawDebugSphere(GetWorld(), SeenPawn -> GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
}

void AAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (NoiseInstigator == nullptr) return;

	UE_LOG(LogTemp, Warning, TEXT("PAWN HEARD"));
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);
}
