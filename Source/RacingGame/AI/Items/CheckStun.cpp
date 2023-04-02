// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckStun.h"
#include "../AICarController.h"
#include "../../HoverTech/FloatingVehicule.h"
bool UCheckStun::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AFloatingVehicule* Vehicule = Cast<AFloatingVehicule>(OwnerComp.GetAIOwner()->GetPawn());
	if (Vehicule->isStun)
	{
		return true;
	}
	return false;
}