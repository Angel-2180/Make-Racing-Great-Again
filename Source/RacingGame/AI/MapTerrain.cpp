// Fill out your copyright notice in the Description page of Project Settings.


#include "MapTerrain.h"
#include "AICar.h"
#include "AICarController.h"

#include "BehaviorTree/BlackboardComponent.h" //blackboard
#include "bbKeys.h"
void UMapTerrain::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAICar* Car = Cast<AAICar>(OwnerComp.GetAIOwner()->GetPawn());
	LeftVector =  MapVector(Car->GetActorLocation() - (Car->GetActorUpVector() * 50), Car->GetActorForwardVector(), Car, 0);
	RightVector = MapVector(Car->GetActorLocation() - (Car->GetActorUpVector() * 50), -Car->GetActorForwardVector(), Car, 1);
	if (ShowDebugPoints)
	{
		DrawDebugPoint(GetWorld(), LeftPointContact, 50, FColor::Red);
		DrawDebugPoint(GetWorld(), RightPointContact, 50, FColor::Red);
	}

	float DistanceLeft = (LeftPointContact - (Car->GetActorLocation() + Car->GetActorScale().Y)).Length();
	float DistanceRight = (RightPointContact - (Car->GetActorLocation() + Car->GetActorScale().Y)).Length();

	AAICarController* controller = Cast<AAICarController>(OwnerComp.GetAIOwner());


	if (DistanceLeft < MinDistanceLeftSide)
	{
		controller->get_blackboard()->SetValueAsBool(bbKeys::UrgentLeft, true);
		controller->get_blackboard()->SetValueAsFloat(bbKeys::ForceofTurn, CalculateAmountOfTurn(DistanceLeft));
	}
	else
		controller->get_blackboard()->SetValueAsBool(bbKeys::UrgentLeft, false);

	if (DistanceRight < MinDistanceRightSide)
	{
		controller->get_blackboard()->SetValueAsBool(bbKeys::UrgentRight, true);
		controller->get_blackboard()->SetValueAsFloat(bbKeys::ForceofTurn, CalculateAmountOfTurn(DistanceRight));
	}
	else
		controller->get_blackboard()->SetValueAsBool(bbKeys::UrgentRight, false);

}

float UMapTerrain::CalculateAmountOfTurn(float Distance)
{
	return 0.1f;
}

FVector UMapTerrain::MapVector(FVector baseVector, FVector VecToRotate, AAICar* Car, int LeftOrRight)
{
	FVector CurrentVector = baseVector;
	FVector Radius = FVector(0,0, -5000);
	float angledeg = 0;
	FVector PointOfContact;

	FVector PrevVector;
	for(int i = 0; i < 150; ++i)
	{
		FHitResult OutHit;
		FCollisionQueryParams CollisionParams = FCollisionQueryParams();
		CollisionParams.AddIgnoredActor(Car);
		

		FVector RotateValue = Radius.RotateAngleAxis(angledeg, VecToRotate);
		CurrentVector = baseVector + RotateValue;

		if (GetWorld()->LineTraceSingleByObjectType(OutHit, Car->GetActorLocation(), CurrentVector, FCollisionObjectQueryParams::AllObjects, CollisionParams))
		{
			if (!OutHit.GetActor()->ActorHasTag(Tag)) //take previous point
			{
				if (LeftOrRight == 0)
					LeftPointContact = PointOfContact;
				else
					RightPointContact = PointOfContact;

				return PrevVector;
			}
		}
		else //take previous point
		{
			if (LeftOrRight == 0)
				LeftPointContact = PointOfContact;
			else
				RightPointContact = PointOfContact;

			return PrevVector;
		}
		PointOfContact = OutHit.ImpactPoint;

		PrevVector = CurrentVector;
		angledeg -= 1;

	}
	if (LeftOrRight == 0)
		LeftPointContact = PointOfContact;
	else
		RightPointContact = PointOfContact;

	return CurrentVector;
}
