// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WayPoint.generated.h"

UCLASS()
class RACINGGAME_API AWayPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWayPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(editanywhere, blueprintReadWrite)
		class UStaticMeshComponent* CustomMesh;
	UPROPERTY(editanywhere, blueprintReadWrite)
		class UBoxComponent* TriggerBox;
	UPROPERTY(editanywhere, blueprintReadWrite)
		class UArrowComponent* Arrow;

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(editanywhere, blueprintReadWrite)
		int WayPointNumb;

	UPROPERTY(editanywhere, blueprintReadWrite)
		bool IsLapCounter;
	
	UPROPERTY(editanywhere, blueprintReadWrite)
		bool ShouldResetPlayerRotation;

	UPROPERTY(editanywhere, blueprintReadWrite)
		bool ShouldLockRotation;

	UPROPERTY(editanywhere, blueprintReadWrite)
		bool ShouldBoost;
};
