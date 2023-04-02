// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "RedMushroom.generated.h"

/**
 *
 */
UCLASS()
class RACINGGAME_API ARedMushroom : public AItem
{
	GENERATED_BODY()

		// Sets default values for this actor's properties
		
public:

	ARedMushroom();
	//mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* Mesh;

	//collision sphere
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
		class USphereComponent* CollisionComponent;

	//speed up amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float SpeedUpAmount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// On overlap begin
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
