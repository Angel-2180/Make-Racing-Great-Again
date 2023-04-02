// Fill out your copyright notice in the Description page of Project Settings.


#include "Unstun.h"
#include "../AICarController.h"
#include "../../HoverTech/FloatingVehicule.h"
EBTNodeResult::Type UUnstun::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AFloatingVehicule* Vehicule = Cast<AFloatingVehicule>(owner_comp.GetAIOwner()->GetPawn());
	Vehicule->isStun = false;

	return EBTNodeResult::Succeeded;
}