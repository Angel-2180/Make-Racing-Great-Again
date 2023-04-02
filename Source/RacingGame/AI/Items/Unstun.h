// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Unstun.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API UUnstun : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

};
