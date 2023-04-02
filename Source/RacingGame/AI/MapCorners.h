// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MapCorners.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API UMapCorners : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	FVector MapFrontPoint(class AAICar* Car);

	bool MapSidePoints(AAICar* Car, int LeftOrRight,int amountTODivide);
	bool CheckCorrectDirection(AAICar* Car, int LeftOrRight);
	bool CheckPassablePoint(AAICar* Car, FVector Point);
	bool MapCloserSidePoints(AAICar* Car, int LeftOrRight);

	UPROPERTY(editAnywhere, blueprintReadWrite)
		float DistanceFrontPoint;
	UPROPERTY(editAnywhere, blueprintReadWrite)
		FName Tag;
	UPROPERTY(editAnywhere, blueprintReadWrite)
		bool ShowDebugPoints;
};
