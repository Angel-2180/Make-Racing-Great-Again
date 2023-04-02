// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "EntityAvoidanceAndConfront.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API UEntityAvoidanceAndConfront : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void ExecuteOvertake(class AAICar* Car,APawn* otherVehicle, class AAICarController* controller);
	void UpdateCarSight(class AAICar* Car);

	UPROPERTY(editAnywhere, blueprintReadWrite)
		float MinDistance;
};
