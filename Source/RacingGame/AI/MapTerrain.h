// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MapTerrain.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API UMapTerrain : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	float CalculateAmountOfTurn(float Distance);
	FVector MapVector(FVector baseVector, FVector VecToRotate, class AAICar* Car, int LeftOrRight);

	FVector LeftVector;
	FVector RightVector;

	FVector LeftPointContact;
	FVector RightPointContact;

	UPROPERTY(editAnywhere, blueprintReadWrite)
		FName Tag;
	UPROPERTY(editAnywhere, blueprintReadWrite)
		float MinDistanceLeftSide;

	UPROPERTY(editAnywhere, blueprintReadWrite)
		float MinDistanceRightSide;


	UPROPERTY(editAnywhere, blueprintReadWrite)
		float DangerDistance;

	UPROPERTY(editAnywhere, blueprintReadWrite)
		bool ShowDebugPoints;
};
