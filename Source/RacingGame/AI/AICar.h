// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RacingGame/HoverTech/FloatingVehicule.h"
#include "AICar.generated.h"

/**
 *
 */
UCLASS()
class RACINGGAME_API AAICar : public AFloatingVehicule
{
    GENERATED_BODY()

public:
    AAICar();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    void Steer(FVector direction) const;
    void Throttle(float Amount) const;

    UFUNCTION(BlueprintCallable)
        void OnSeePawn(APawn* OtherPawn);

    bool CheckSeeingPawn(const APawn* pawn) const;

    void PushToGround();

    void CheckGround();

    UPROPERTY(editAnywhere, BlueprintReadWrite, Category = AI)
        class UPawnSensingComponent* PerceptionTest;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wheels, meta = (AllowPrivateAccess = "true"))
        class UPitchControl* pitchController;

    std::vector<APawn*> PawnsInMemory;

    std::vector<APawn*> CurrentSeeingPawns;

    FVector throttleVector;

    float CurrentSpeed;
    bool ShouldControlPitch = false;
    //FOR RESPAWNING

    void Respawn();

    float CurrentTimeWithoutGround;
    bool CanTurn = true;

    //Rotations

    void LerpRotation(float Alpha);
    bool ShouldRotate = false;
    float RotationSpeed = 0.05f;
    FRotator NewRotation;
    float CurrentAlpha = 0;
};