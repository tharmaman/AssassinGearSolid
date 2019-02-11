// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

// adding forward declarations to speed up compile time
class UBoxComponent;
class UStaticMeshComponent;
class UArrowComponent;

UCLASS()
class ASSASSINGEARSOLID_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* MeshComp;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UBoxComponent* OverlapComp;

    // marked with UFUNCTION to bind to overlap event
    UFUNCTION()
    void HandleOverlapLaunchpad(
            UPrimitiveComponent* OverlappedComponent,
            AActor* OtherActor,
            UPrimitiveComponent* OtherComp,
            int32 OtherBodyIndex,
            bool bFromSweep,
            const FHitResult & SweepResult
    );

    /**
     * Total impulse added to the character on overlap
     */
    UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
    float LaunchStrength;


    UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
    float LaunchPitchAngle;


};
