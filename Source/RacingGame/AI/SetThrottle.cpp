// Fill out your copyright notice in the Description page of Project Settings.


#include "SetThrottle.h"
#include "AICar.h"
#include "AICarController.h" 
EBTNodeResult::Type USetThrottle::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAICar* Car = Cast<AAICar>(owner_comp.GetAIOwner()->GetPawn());

	Car->Throttle(Speed);
	return EBTNodeResult::Succeeded;
}
