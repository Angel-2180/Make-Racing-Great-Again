// Fill out your copyright notice in the Description page of Project Settings.


#include "Brake.h"
#include "AICarController.h"
#include "AICar.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "bbKeys.h"
EBTNodeResult::Type UBrake::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAICarController* controller = Cast<AAICarController>(owner_comp.GetAIOwner());
	AAICar* Car = Cast<AAICar>(controller->GetPawn());
	float BrakeIntensity = controller->get_blackboard()->GetValueAsFloat(bbKeys::BrakeIntensity);
	//Car->Brake(BrakeIntensity);
	return EBTNodeResult::Succeeded;
}