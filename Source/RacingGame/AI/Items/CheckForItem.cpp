// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckForItem.h"
#include "../AICarController.h"
#include "../../HoverTech/FloatingVehicule.h"

#include "BehaviorTree/BlackboardComponent.h" //blackboard
#include "../bbKeys.h"
#include "../../Items/EMP.h"
#include "../../GreenShell.h"
#include "../../Items/RedMushroom.h"
bool UCheckForItem::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AFloatingVehicule* Vehicule = Cast<AFloatingVehicule>(OwnerComp.GetAIOwner()->GetPawn());

	AAICarController* Controller = Cast<AAICarController>(OwnerComp.GetAIOwner());



	if (Vehicule->GetHeldItem() != nullptr)
	{
		if (Vehicule->GetHeldItem()->Get() != nullptr)
		{


			if (Vehicule->GetHeldItem()->Get()->IsChildOf(AEMP::StaticClass()))
			{
				FString a = "Banana";
				Controller->get_blackboard()->SetValueAsString(bbKeys::ItemText, a);
			}
			if (Vehicule->GetHeldItem()->Get()->IsChildOf(AGreenShell::StaticClass()))
			{
				FString a = "GShell";
				Controller->get_blackboard()->SetValueAsString(bbKeys::ItemText, a);
			}
			if (Vehicule->GetHeldItem()->Get()->IsChildOf(ARedMushroom::StaticClass()))
			{
				FString a = "Shroom";
				Controller->get_blackboard()->SetValueAsString(bbKeys::ItemText, a);
			}

			return true;
		}
	}

	return false;
}