// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionCalculator.h"
#include "../HoverTech/FloatingVehicule.h"
#include "../Features/WayPoint.h"
#include <Kismet/GameplayStatics.h>
// Sets default values
APositionCalculator::APositionCalculator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APositionCalculator::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFloatingVehicule::StaticClass(), Vehicules);
}

// Called every frame
void APositionCalculator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateCarPositions();

}

void APositionCalculator::UpdateCarPositions()
{
	TArray<AActor*> TmpVehicules = Vehicules;
	for (int i = 0; i < Vehicules.Num(); ++i)
	{
		AFloatingVehicule* HighestPlaceVehicule = GetHighestPlaceActor(TmpVehicules);
		TmpVehicules.Remove(HighestPlaceVehicule);
		HighestPlaceVehicule->CurrentPosition = i + 1;
	}
}

AFloatingVehicule* APositionCalculator::GetHighestPlaceActor(TArray<AActor*> CurrVehicules)
{
	AFloatingVehicule* CurrentHighestActor = nullptr;

	for (int i = 0; i < CurrVehicules.Num(); ++i)
	{
		if (!CurrentHighestActor)
			CurrentHighestActor = Cast<AFloatingVehicule>(CurrVehicules[i]);
		else
		{
			AFloatingVehicule* OtherVehicule = Cast<AFloatingVehicule>(CurrVehicules[i]);
			if (CurrentHighestActor->CurrentLap < OtherVehicule->CurrentLap)
			{
				CurrentHighestActor = OtherVehicule;
			}
			else 
			{	
				if (CurrentHighestActor->CurrentWayPoint && OtherVehicule->CurrentWayPoint)
				{
					if ((CurrentHighestActor->CurrentWayPoint->WayPointNumb < OtherVehicule->CurrentWayPoint->WayPointNumb ||
						CurrentHighestActor->NumbWayPointsPassed < OtherVehicule->NumbWayPointsPassed) && CurrentHighestActor->CurrentLap >= OtherVehicule->CurrentLap)
					{
						CurrentHighestActor = OtherVehicule;
					}
					else if (CurrentHighestActor->CurrentWayPoint->WayPointNumb == OtherVehicule->CurrentWayPoint->WayPointNumb && CurrentHighestActor->CurrentLap >= OtherVehicule->CurrentLap)
					{
						float HighestActorDistance = FVector::Distance(CurrentHighestActor->GetActorLocation(), CurrentHighestActor->CurrentWayPoint->GetActorLocation());
						float OtherActorDistance = FVector::Distance(OtherVehicule->GetActorLocation(), OtherVehicule->CurrentWayPoint->GetActorLocation());
						if (HighestActorDistance < OtherActorDistance)
							CurrentHighestActor = OtherVehicule;
					}
				}
			}
		}
	}
	return CurrentHighestActor;
}
