// Fill out your copyright notice in the Description page of Project Settings.


#include "Corner.h"
#include "AICar.h"
#include "AICarController.h"

EBTNodeResult::Type UCorner::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAICar* Car = Cast<AAICar>(owner_comp.GetAIOwner()->GetPawn());
	if(Car->CanTurn)
		Car->Steer(FVector(SteeringForce * LeftOrRight, 0, 0));

	return EBTNodeResult::Succeeded;
}