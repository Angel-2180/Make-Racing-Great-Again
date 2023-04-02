// Fill out your copyright notice in the Description page of Project Settings.

#include "UseShroom.h"
#include "BehaviorTree/BlackboardComponent.h" //blackboard
#include "../bbKeys.h"

#include "../AICarController.h"
#include "../AICar.h"
#include "../../Items/RedMushroom.h"
EBTNodeResult::Type UUseShroom::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
    AAICar* Vehicle = Cast<AAICar>(owner_comp.GetAIOwner()->GetPawn());
    AAICarController* Controller = Cast<AAICarController>(owner_comp.GetAIOwner());
    if (!Once)
    {
        FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UUseShroom::EndSpeed, Controller, Vehicle);
        GetWorld()->GetTimerManager().SetTimer(UnusedHandle, TimerDelegate, 1, false);
        Once = true;
    }
   

    

    return EBTNodeResult::Succeeded;
}

void UUseShroom::EndSpeed(AAICarController* Controller, class AAICar* Car)
{
    Once = false;
   

    Controller->get_blackboard()->SetValueAsString(bbKeys::ItemText, FString(""));

    GetWorld()->GetTimerManager().ClearTimer(UnusedHandle);
    Car->GetHeldItem() = nullptr;
}