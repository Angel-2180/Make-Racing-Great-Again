// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PositionCalculator.generated.h"

UCLASS()
class RACINGGAME_API APositionCalculator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APositionCalculator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<AActor*> Vehicules;

	void UpdateCarPositions();


	class AFloatingVehicule* GetHighestPlaceActor(TArray<AActor*> CurrVehicules);
};
