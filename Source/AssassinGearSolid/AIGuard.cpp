// Fill out your copyright notice in the Description page of Project Settings.

#include "AIGuard.h"
#include "Classes/Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "Public/TimerManager.h"

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

	OriginalRotation = GetActorRotation();
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

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;

	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);

	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AAIGuard::ResetOrientation, 3.0f);
}

void AAIGuard::ResetOrientation()
{
	SetActorRotation(OriginalRotation);
}
