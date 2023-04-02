// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnOnLoop.h"
#include "AICar.h"
#include "AICarController.h" 
#include "Components/BoxComponent.h"
//loop
#include "../Loop/Loop.h"
#include "Components/SplineComponent.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
EBTNodeResult::Type UTurnOnLoop::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{


	AAICar* Car = Cast<AAICar>(owner_comp.GetAIOwner()->GetPawn());
	FHitResult OutHit;

	FCollisionQueryParams CollisionParams = FCollisionQueryParams(FName("Trigger"), true);
	CollisionParams.AddIgnoredActor(Car);

	FVector Down = Car->GetActorLocation() - (Car->GetActorUpVector() * 500);

	if (GetWorld()->LineTraceSingleByObjectType(OutHit, Car->GetActorLocation(), Down, FCollisionObjectQueryParams::AllObjects, CollisionParams))
	{
		ALoop* loop = Cast<ALoop>(OutHit.GetActor());
		if (!loop)
		{
			return EBTNodeResult::Succeeded;
		}
		USplineComponent* LoopSpline = loop->Spline;
		FSplineCurves SplineCurves = LoopSpline->SplineCurves;
		int32 totalSplines = LoopSpline->GetNumberOfSplinePoints();
		int BestIndex = GetClosestSplinePoint(Car, loop, LoopSpline, totalSplines);
		
		FVector vec = LoopSpline->GetLocationAtSplinePoint(BestIndex, ESplineCoordinateSpace::World);
		FVector Diff = vec - Car->GetActorLocation();
		Diff.Normalize();
	

		if (CheckifPointInFront(Car, LoopSpline->GetLocationAtSplinePoint(BestIndex, ESplineCoordinateSpace::World)) && (LoopSpline->GetLocationAtSplinePoint(BestIndex, ESplineCoordinateSpace::World) - Car->GetActorLocation()).Length() > 350)
		{
			//if(Car->IsVehiculeGrounded())
			Car->GetBoxComponent()->AddForce(Diff * 5000000); // CHANGE THIS DEPENDING ON SCALE
		}
	}
	return EBTNodeResult::Succeeded;
}

int UTurnOnLoop::GetClosestSplinePoint(AAICar* Car, ALoop* loop, USplineComponent* LoopSpline, int Indices)
{
	int BestIndex = -1;
	float BestDistance = 100000000;
	int i;
	for (i = 0; i < Indices; ++i)
	{
		float Distance = (Car->GetActorLocation() - LoopSpline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World)).Length();
		if (Distance < BestDistance && CheckifPointInFront(Car, LoopSpline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World)))
		{
			BestDistance = Distance;
			BestIndex = i;
		}
	}
	return BestIndex;
}

bool UTurnOnLoop::CheckifPointInFront(AAICar* Car, FVector Point)
{
	FVector Diff = Point - Car->GetActorLocation();
	return FVector::DotProduct(Diff, Car->GetActorForwardVector()) > 0 ? true : false;
}