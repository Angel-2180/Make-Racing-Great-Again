// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "EMP.generated.h"

/**
 *
 */
UCLASS()
class RACINGGAME_API AEMP : public AItem
{
    GENERATED_BODY()

public:
    AEMP();

    //mesh
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item | Mesh")
        class UStaticMeshComponent* Mesh;

    //collision box
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item | Collision")
        class UBoxComponent* CollisionBox;

    //projectile component
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item | Projectile")
        class UProjectileMovementComponent* ProjectileMovement;

protected:

    virtual void Tick(float DeltaTime) override;

public:

    //hit function
    UFUNCTION()
        void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    UFUNCTION()
        void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    //begin play
    virtual void BeginPlay() override;
};
