// Fill out your copyright notice in the Description page of Project Settings.


#include "PullAIBackOnRoad.h"
#include "AICarController.h"
#include "AICar.h"
EBTNodeResult::Type UPullAIBackOnRoad::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAICarController* controller = Cast<AAICarController>(owner_comp.GetAIOwner());
	AAICar* Car = Cast<AAICar>(controller->GetPawn());
	FVector PullPoint = Car->PointToRespawn;
//	PullPoint.Z = Car->GetActorLocation().Z;
	Car->SetActorLocation(PullPoint);
	Car->SetActorRotation(Car->RotationToRespawn);

	return EBTNodeResult::Succeeded;
}