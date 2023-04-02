// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Corner.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API UCorner : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;


	UPROPERTY(editAnywhere, blueprintReadWrite)
		int LeftOrRight;

	UPROPERTY(editAnywhere, blueprintReadWrite)
		float SteeringForce;
};
