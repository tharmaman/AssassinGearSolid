// Fill out your copyright notice in the Description page of Project Settings.

#include "LaunchPad.h"
#include "Components/BoxComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Classes/GameFramework/Character.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
    OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
    OverlapComp -> SetBoxExtent(FVector(75, 75, 50));
    RootComponent = OverlapComp;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp -> SetupAttachment(RootComponent);

    /**
     * Bind to Event
     */
    OverlapComp -> OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::OverlapLaunchPad);

    LaunchStrength = 1500.0f;
    LaunchPitchAngle = 35.0f;
}

void ALaunchPad::OverlapLaunchPad(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                  UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult &SweepResult)
{
    // Make rotator with our specified 'pitch' and convert to a direction vector * intensity
    FRotator LaunchDirection = GetActorRotation();
    LaunchDirection.Pitch += LaunchPitchAngle;
    FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

    ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);

    if (OtherCharacter)
    {
        // Launch Player! Both booleans give consistent launch velocity by ignoring player velocity
        OtherCharacter -> LaunchCharacter(LaunchVelocity, true, true);

        // Spawn FX
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
    }
    /// Did not overlap a player, but check if actor can simulate phsyics for launch
    else if (OtherComp && OtherComp -> IsSimulatingPhysics())
    {
        OtherComp -> AddImpulse(LaunchVelocity, NAME_None, true);

        // Spawn FX
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
    }
}

