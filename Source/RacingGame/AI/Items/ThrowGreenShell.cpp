// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowGreenShell.h"
#include "BehaviorTree/BlackboardComponent.h" //blackboard
#include "../bbKeys.h"

#include "../../GreenShell.h"
#include "../AICarController.h"
#include "../../HoverTech/FloatingVehicule.h"
#include "Components/ArrowComponent.h"
EBTNodeResult::Type UThrowGreenShell::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AFloatingVehicule* Vehicle = Cast<AFloatingVehicule>(owner_comp.GetAIOwner()->GetPawn());

	auto Item = Vehicle->GetHeldItem()->Get();
	if (!Item)
		return EBTNodeResult::Succeeded;

	
	FVector SpawnLocation = Vehicle->GetActorLocation() + Vehicle->GetActorForwardVector() * 500;
	FRotator SpawnRotation = Vehicle->GetActorRotation();

	this->GetWorld()->SpawnActor<AItem>(Item, SpawnLocation, SpawnRotation);

	Vehicle->GetHeldItem() = nullptr;

	AAICarController* controller = Cast<AAICarController>(owner_comp.GetAIOwner());

	controller->get_blackboard()->SetValueAsString(bbKeys::ItemText, FString(""));

	return EBTNodeResult::Succeeded;
}