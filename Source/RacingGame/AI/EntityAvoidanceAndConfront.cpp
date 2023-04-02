// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityAvoidanceAndConfront.h"
#include "AICar.h"
#include "AICarController.h"

#include "BehaviorTree/BlackboardComponent.h" //blackboard
#include "bbKeys.h"

#include "../Player/PlayerClass.h"

void UEntityAvoidanceAndConfront::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAICar* Car = Cast<AAICar>(OwnerComp.GetAIOwner()->GetPawn());
	AAICarController* controller = Cast<AAICarController>(OwnerComp.GetAIOwner());

	UpdateCarSight(Car);
	for (auto& it : Car->CurrentSeeingPawns)
	{
		APlayerClass* player = Cast<APlayerClass>(it);//check if Player 
		if (player != nullptr)
		{
			ExecuteOvertake(Car, player, controller);
			return;
		}
		AAICar* OtherCar = Cast<AAICar>(it); //check for Other Cars
		if (OtherCar != nullptr)
		{
			ExecuteOvertake(Car, OtherCar, controller);
			return;
		}
	}

	controller->get_blackboard()->SetValueAsBool(bbKeys::Brake, false);
	controller->get_blackboard()->SetValueAsBool(bbKeys::OvertakeRight, false);
	controller->get_blackboard()->SetValueAsBool(bbKeys::OvertakeLeft, false);
	controller->get_blackboard()->SetValueAsBool(bbKeys::Accelerate, false);

}

void UEntityAvoidanceAndConfront::ExecuteOvertake(AAICar* Car, APawn* otherVehicle, AAICarController* controller)
{
	FVector DifferenceVec = otherVehicle->GetActorLocation() - Car->GetActorLocation();
	
	if (DifferenceVec.Length() < MinDistance)
	{
		controller->get_blackboard()->SetValueAsBool(bbKeys::Brake, true);
		return;
	}
	DifferenceVec.Normalize();
	controller->get_blackboard()->SetValueAsBool(bbKeys::Brake, false);

	if (FVector::DotProduct(Car->GetActorRightVector(), DifferenceVec) < 0)
	{
		if ((FMath::Abs(Car->GetActorLocation().Y - otherVehicle->GetActorLocation().Y) > Car->GetActorScale().Y * 1.2) 
			&& !controller->get_blackboard()->GetValueAsBool(bbKeys::CornerLeft))
		{
			controller->get_blackboard()->SetValueAsBool(bbKeys::OvertakeRight, true); //right
		}
		else
		{
			controller->get_blackboard()->SetValueAsBool(bbKeys::Accelerate, true);
		}

	}
	else
	{
		if (FMath::Abs(Car->GetActorLocation().Y - otherVehicle->GetActorLocation().Y) > Car->GetActorScale().Y * 1.2
			&& !controller->get_blackboard()->GetValueAsBool(bbKeys::CornerRight))
		{
			controller->get_blackboard()->SetValueAsBool(bbKeys::OvertakeLeft, true); //left
		}
		else
		{
			controller->get_blackboard()->SetValueAsBool(bbKeys::Accelerate, true);
		}
	}
}

void UEntityAvoidanceAndConfront::UpdateCarSight(AAICar* Car)
{
	for (auto& it : Car->PawnsInMemory)
	{
		APawn* SeeablePawn = it;
		if (SeeablePawn->Controller && Car)
		{
			if (Car->CheckSeeingPawn(SeeablePawn))
			{
				if (std::find(Car->CurrentSeeingPawns.begin(), Car->CurrentSeeingPawns.end(), SeeablePawn) == Car->CurrentSeeingPawns.end())
				{
					Car->CurrentSeeingPawns.emplace_back(SeeablePawn);
				}
			}
			else
			{
				if (std::find(Car->CurrentSeeingPawns.begin(), Car->CurrentSeeingPawns.end(), SeeablePawn) != Car->CurrentSeeingPawns.end())
				{
					Car->CurrentSeeingPawns.erase(std::find(Car->CurrentSeeingPawns.begin(), Car->CurrentSeeingPawns.end(), SeeablePawn));
				}
			}
		}
	}
}
