// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SetThrottle.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API USetThrottle : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Speed;

};
