// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckForBrake.h"
#include "AICar.h"
#include "AICarController.h"
#include "../Volumes/AICarTriggerBox.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "bbKeys.h"
bool UCheckForBrake::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAICar* Car = Cast<AAICar>(OwnerComp.GetAIOwner()->GetPawn());

	FVector EndForward = Car->GetActorLocation() + (Car->GetActorForwardVector() * BrakeDistance);
	FHitResult OutHit;

	FCollisionQueryParams CollisionParams = FCollisionQueryParams(FName("Trigger"), true);
	DrawDebugLine(GetWorld(), Car->GetActorLocation(), EndForward, FColor::Blue, false, 1, 0, 5);
	if (GetWorld()->LineTraceSingleByObjectType(OutHit, Car->GetActorLocation(), EndForward, FCollisionObjectQueryParams::AllObjects, CollisionParams))
	{
		

		if (OutHit.GetActor()->GetClass()->IsChildOf(AAICarTriggerBox::StaticClass()) && Car->GetVelocity().Length() > MinVelocity)
		{
			float Brake = 1 - ((OutHit.Distance - MinDistance) / BrakeDistance);
			if (OutHit.Distance - MinDistance < 0)
			{
				Brake = 1;
			}
			
			AAICarController* controller = Cast<AAICarController>(OwnerComp.GetAIOwner());
			controller->get_blackboard()->SetValueAsFloat(bbKeys::BrakeIntensity, Brake);
			return true;
		}

	}
	return false;
}