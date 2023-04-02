// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "CheckForBrake.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API UCheckForBrake : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
		virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float BrakeDistance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MinVelocity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MinDistance;
};
