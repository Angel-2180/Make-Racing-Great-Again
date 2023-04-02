// Fill out your copyright notice in the Description page of Project Settings.


#include "Turn.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AICarController.h"
#include "AICar.h"
#include "bbKeys.h"
EBTNodeResult::Type UTurn::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAICarController* controller = Cast<AAICarController>(owner_comp.GetAIOwner());
	AAICar* Car = Cast<AAICar>(controller->GetPawn());
	
	if (controller->get_blackboard()->GetValueAsBool(bbKeys::UrgentLeft))
	{
		Car->Steer(FVector(controller->get_blackboard()->GetValueAsFloat(bbKeys::ForceofTurn), 0, 0));
		controller->get_blackboard()->SetValueAsInt(bbKeys::AmountofTurn, 1);
		controller->get_blackboard()->SetValueAsFloat(bbKeys::TotalForceofTurn, controller->get_blackboard()->GetValueAsFloat(bbKeys::TotalForceofTurn) + controller->get_blackboard()->GetValueAsFloat(bbKeys::ForceofTurn));
		//Car->GetBoxComponent()->AddForce(-Car->GetActorRightVector() * 1000000);
		return EBTNodeResult::Succeeded;
	}
	else if (controller->get_blackboard()->GetValueAsBool(bbKeys::UrgentRight))
	{
		Car->Steer(FVector(-controller->get_blackboard()->GetValueAsFloat(bbKeys::ForceofTurn), 0, 0));
		controller->get_blackboard()->SetValueAsFloat(bbKeys::TotalForceofTurn, controller->get_blackboard()->GetValueAsFloat(bbKeys::TotalForceofTurn) - controller->get_blackboard()->GetValueAsFloat(bbKeys::ForceofTurn));
		controller->get_blackboard()->SetValueAsInt(bbKeys::AmountofTurn, -1);
		//Car->GetBoxComponent()->AddForce(Car->GetActorRightVector() * 1000000);
		return EBTNodeResult::Succeeded;
	}


	return EBTNodeResult::Succeeded;
}
