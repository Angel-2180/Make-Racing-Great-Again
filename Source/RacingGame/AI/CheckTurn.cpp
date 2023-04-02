// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckTurn.h"
#include "AICar.h"
#include "AICarController.h"
#include "../Volumes/AICarTriggerBox.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "bbKeys.h"
bool UCheckTurn::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const //DEPRECATED
{
	AAICar* Car = Cast<AAICar>(OwnerComp.GetAIOwner()->GetPawn());

	FVector Down = Car->GetActorLocation() - (Car->GetActorUpVector() * 100);
	FHitResult OutHit;
	AAICarController* controller = Cast<AAICarController>(OwnerComp.GetAIOwner());
	FCollisionQueryParams CollisionParams = FCollisionQueryParams(FName("Trigger"), true);

	DrawDebugLine(GetWorld(), Car->GetActorLocation(), Down, FColor::Green, false, 1, 0, 5);
	if (GetWorld()->LineTraceSingleByObjectType(OutHit, Car->GetActorLocation(), Down, FCollisionObjectQueryParams::AllObjects, CollisionParams))
	{
		AActor* platform = OutHit.GetActor();

		float Angle = FMath::RadiansToDegrees(acos(FVector::DotProduct(platform->GetActorForwardVector(), Car->GetActorForwardVector())));
		
			
		float amount = Angle / 10;

		if (Car->GetActorRotation().Yaw > platform->GetActorRotation().Yaw)
		{
			//controller->get_blackboard()->SetValueAsBool(bbKeys::ShouldTurnLeft, true);
			//controller->get_blackboard()->SetValueAsFloat(bbKeys::TurnAmount, -amount);
		}
		else
		{
			//controller->get_blackboard()->SetValueAsBool(bbKeys::ShouldTurnLeft, false);
			//controller->get_blackboard()->SetValueAsFloat(bbKeys::TurnAmount, amount);
		}

		if (Angle > 3)
		{
			return true;
		}
	}

	FHitResult OutHit2;
	FVector Right = Car->GetActorLocation() + (Car->GetActorRightVector() * 700);
	DrawDebugLine(GetWorld(), Car->GetActorLocation(), Right, FColor::Blue);
	if (GetWorld()->LineTraceSingleByObjectType(OutHit2, Car->GetActorLocation(), Right, FCollisionObjectQueryParams::AllObjects, CollisionParams))
	{

		if (OutHit2.GetActor()->GetClass()->IsChildOf(AAICarTriggerBox::StaticClass()))
		{
			if ((OutHit2.Location - Car->GetActorLocation()).Length() < 500)
			{
				//controller->get_blackboard()->SetValueAsBool(bbKeys::ShouldTurnLeft, true);
				//controller->get_blackboard()->SetValueAsFloat(bbKeys::TurnAmount, -0.3);
				return true;
			}
		}
	}
	FHitResult OutHit3;
	FVector Left = Car->GetActorLocation() - (Car->GetActorRightVector() * 700);
	DrawDebugLine(GetWorld(), Car->GetActorLocation(), Left, FColor::Blue);
	if (GetWorld()->LineTraceSingleByObjectType(OutHit3, Car->GetActorLocation(), Left, FCollisionObjectQueryParams::AllObjects, CollisionParams))
	{
		if (OutHit3.GetActor()->GetClass()->IsChildOf(AAICarTriggerBox::StaticClass()))
		{
			if ((OutHit3.Location - Car->GetActorLocation()).Length() < 500)
			{
				//controller->get_blackboard()->SetValueAsBool(bbKeys::ShouldTurnLeft, false);
				//controller->get_blackboard()->SetValueAsFloat(bbKeys::TurnAmount, 0.3);
				return true;
			}
		}
	}
	//
	return false;
}