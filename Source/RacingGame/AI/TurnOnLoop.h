// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Actor.h"
#include "TurnOnLoop.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API UTurnOnLoop : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

	UPROPERTY(editAnywhere, blueprintReadWrite)
		float LeftOrRight;

	int GetClosestSplinePoint(class AAICar* Car, class ALoop* loop, class USplineComponent* LoopSpline, int Indices);
	bool CheckifPointInFront(AAICar* Car, FVector Point);
};
