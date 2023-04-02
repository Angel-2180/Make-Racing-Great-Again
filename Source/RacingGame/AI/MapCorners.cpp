// Fill out your copyright notice in the Description page of Project Settings.


#include "MapCorners.h"
#include "AICar.h"
#include "AICarController.h"

#include "BehaviorTree/BlackboardComponent.h" //blackboard
#include "bbKeys.h"
#include "../Features/WayPoint.h"
#include "Components/ArrowComponent.h"
void UMapCorners::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAICar* Car = Cast<AAICar>(OwnerComp.GetAIOwner()->GetPawn());

	FVector Front = MapFrontPoint(Car);

	if(ShowDebugPoints)
		DrawDebugPoint(GetWorld(), Front, 50, FColor::Blue);

	FHitResult OutHit;
	FCollisionQueryParams CollisionParams = FCollisionQueryParams();
	CollisionParams.AddIgnoredActor(Car);
	AAICarController* controller = Cast<AAICarController>(OwnerComp.GetAIOwner());

	if (GetWorld()->LineTraceSingleByObjectType(OutHit, Front, Front - Car->GetActorUpVector() * 1000, FCollisionObjectQueryParams::AllObjects, CollisionParams))
	{
		if (OutHit.GetActor()->ActorHasTag(Tag))
		{
			controller->get_blackboard()->SetValueAsBool(bbKeys::CornerRight, false);
			controller->get_blackboard()->SetValueAsBool(bbKeys::CornerLeft, false);
			return;
		}
	}

	if (MapSidePoints(Car, 1, 2) && CheckCorrectDirection(Car, 1)) //turn right
	{
		controller->get_blackboard()->SetValueAsBool(bbKeys::CornerRight, true);
	}
	else if (MapSidePoints(Car, -1, 2) && CheckCorrectDirection(Car, -1)) //Turn left
	{
		controller->get_blackboard()->SetValueAsBool(bbKeys::CornerLeft, true);
	}
	else if(MapCloserSidePoints(Car, -1))
	{
		controller->get_blackboard()->SetValueAsBool(bbKeys::CornerLeft, true);
	}
	else if (MapCloserSidePoints(Car, 1))
	{
		controller->get_blackboard()->SetValueAsBool(bbKeys::CornerRight, true);
	}
}

FVector UMapCorners::MapFrontPoint(AAICar* Car)
{
	return Car->GetActorLocation() + (Car->GetActorForwardVector() * DistanceFrontPoint);
}

bool UMapCorners::MapSidePoints(AAICar* Car, int LeftOrRight, int amountTODivide) // 1 or -1
{
	FVector side = MapFrontPoint(Car) + (LeftOrRight * Car->GetActorRightVector() * DistanceFrontPoint) / amountTODivide;

	FHitResult OutHit;
	FCollisionQueryParams CollisionParams = FCollisionQueryParams();
	CollisionParams.AddIgnoredActor(Car);

	if(ShowDebugPoints)
		DrawDebugPoint(GetWorld(), side, 50, FColor::Green);

	if (GetWorld()->LineTraceSingleByObjectType(OutHit, side, side - Car->GetActorUpVector() * 1000, FCollisionObjectQueryParams::AllObjects, CollisionParams))
	{
		if (OutHit.GetActor()->ActorHasTag(Tag))
		{
			return true;
		}
	}
	return false;
}

bool UMapCorners::MapCloserSidePoints(AAICar* Car, int LeftOrRight)
{
	FVector side = Car->GetActorLocation() + (Car->GetActorRightVector() * LeftOrRight) * 1000;

	FHitResult OutHit;
	FCollisionQueryParams CollisionParams = FCollisionQueryParams();
	CollisionParams.AddIgnoredActor(Car);

	if (ShowDebugPoints)
		DrawDebugPoint(GetWorld(), side, 50, FColor::Green);

	if (GetWorld()->LineTraceSingleByObjectType(OutHit, side, side - Car->GetActorUpVector() * 1000, FCollisionObjectQueryParams::AllObjects, CollisionParams))
	{
		if (OutHit.GetActor()->ActorHasTag(Tag) && CheckPassablePoint(Car, side))
		{
			return true;
		}
	}
	return false;
}


bool UMapCorners::CheckCorrectDirection(AAICar* Car, int LeftOrRight)
{
	FVector side = MapFrontPoint(Car) + (LeftOrRight * Car->GetActorRightVector() * DistanceFrontPoint);
	FVector CarVec = side - Car->GetActorLocation();
	if (Car->CurrentWayPoint)
		return FVector::DotProduct(CarVec, Car->CurrentWayPoint->Arrow->GetForwardVector()) < 0 ? false : true;
	else
		return true;
}

bool UMapCorners::CheckPassablePoint(AAICar* Car, FVector Point)
{
	FHitResult OutHit;
	FCollisionQueryParams CollisionParams = FCollisionQueryParams();
	CollisionParams.AddIgnoredActor(Car);

	FVector Distance = Point - Car->GetActorLocation();
	Distance.Normalize();
	FVector FinalPoint = Car->GetActorLocation() + Distance * 10;
	if (GetWorld()->LineTraceSingleByObjectType(OutHit, FinalPoint, FinalPoint - Car->GetActorUpVector() * 1000, FCollisionObjectQueryParams::AllObjects, CollisionParams))
	{
		if (OutHit.GetActor()->ActorHasTag(Tag))
		{
			return true;
		}
	}
	return false;
}