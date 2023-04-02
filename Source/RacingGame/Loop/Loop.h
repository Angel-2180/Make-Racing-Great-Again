// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Loop.generated.h"

UCLASS()
class RACINGGAME_API ALoop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALoop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(editAnywhere, blueprintReadWrite)
		class UStaticMeshComponent* MeshComponent;

	UPROPERTY(editAnywhere, blueprintReadWrite)
		class USplineComponent* Spline;

};
