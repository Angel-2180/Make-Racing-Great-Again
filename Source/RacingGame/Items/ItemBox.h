// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBox.generated.h"

UCLASS()
class RACINGGAME_API AItemBox : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AItemBox();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
        TArray<TSubclassOf<class AItem>> Items;

    //mesh
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
        class UStaticMeshComponent* Mesh;

    //collision box
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
        class UBoxComponent* CollisionComponent;

    //model for mesh
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items ")
        class UStaticMesh* MeshModel;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    //on overlap begin
    UFUNCTION()
        void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
    void Disable();

    void Enable();

    struct FTimerHandle respawnTimer;
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    float respawnTime = 5.f;

    //oscillator value
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Oscillator")
        float oscillationValue = 0.f;

    //oscillator speed
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Oscillator")
        float oscillationSpeed = 3.f;

    //oscillator amplitude
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Oscillator")
        float oscillationAmplitude = 20.f;

    //oscillator offset
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Oscillator")
        float oscillationOffset = 0.f;
};
