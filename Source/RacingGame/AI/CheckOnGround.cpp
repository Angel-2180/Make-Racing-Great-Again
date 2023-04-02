// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckOnGround.h"
#include "AICarController.h"
#include "../AI/AICar.h"
bool UCheckOnGround::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{

	AAICar* Car = Cast<AAICar>(OwnerComp.GetAIOwner()->GetPawn());

	FVector EndDown = Car->GetActorLocation() - (Car->GetActorUpVector() * 10000);
	
	FHitResult OutHit;

	FCollisionQueryParams CollisionParams = FCollisionQueryParams();
	CollisionParams.AddIgnoredActor(Car);
	if (GetWorld()->LineTraceSingleByObjectType(OutHit, Car->GetActorLocation(), EndDown, FCollisionObjectQueryParams::AllObjects, CollisionParams))
	{
		if (OutHit.GetActor()->ActorHasTag(GroundTag))
			return true;
	}
	
	if (Car->CurrentTimeWithoutGround >= TimeBeforeDeactivation)
	{
		return false;
	}
	return true;
}