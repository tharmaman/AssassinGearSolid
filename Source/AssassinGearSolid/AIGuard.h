// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIGuard.generated.h"

class UPawnSensingComponent;	// forward declaring

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,

	Suspicious,

	Alerted
};

UCLASS()
class ASSASSINGEARSOLID_API AAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetOrientation();

	FRotator OriginalRotation;

	FTimerHandle TimerHandle_ResetOrientation;

	UPROPERTY(ReplicatedUsing=OnRep_GuardState)
	EAIState GuardState;

	UFUNCTION()
	void OnRep_GuardState();

	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category ="AI")
	void OnStateChanged(EAIState NewState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
