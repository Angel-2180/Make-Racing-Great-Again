// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetTurn.h"
#include "AICar.h"

#include "BehaviorTree/BlackboardComponent.h" //blackboard
#include "AICarController.h"
#include "bbKeys.h"
#include "../Features/WayPoint.h"
#include "Components/ArrowComponent.h"
EBTNodeResult::Type UResetTurn::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAICarController* controller = Cast<AAICarController>(owner_comp.GetAIOwner());
	AAICar* Car = Cast<AAICar>(owner_comp.GetAIOwner()->GetPawn());
	if(Car->CurrentWayPoint)
		Car->SetActorRotation(Car->CurrentWayPoint->Arrow->GetComponentRotation());
	//if (controller->get_blackboard()->GetValueAsInt(bbKeys::AmountofTurn) < 0)
	//{
	//	Car->Steer(FVector(-controller->get_blackboard()->GetValueAsFloat(bbKeys::TotalForceofTurn), 0, 0));
	//}
	//else 
	//{
	//	Car->Steer(FVector(-controller->get_blackboard()->GetValueAsFloat(bbKeys::TotalForceofTurn), 0, 0));
	//}
	//controller->get_blackboard()->SetValueAsFloat(bbKeys::TotalForceofTurn, 0.0f);
	return EBTNodeResult::Succeeded;
}