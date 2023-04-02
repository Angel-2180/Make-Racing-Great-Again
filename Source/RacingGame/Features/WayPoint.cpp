// Fill out your copyright notice in the Description page of Project Settings.
#include "WayPoint.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
//Actor References
#include "../HoverTech/FloatingVehicule.h"
#include <Kismet/GameplayStatics.h>
#include "../AI/AICar.h"
#include "../Items/RedMushroom.h"
#include "BehaviorTree/BlackboardComponent.h" //blackboard
#include "../AI/bbKeys.h"
#include "../AI/AICarController.h"
// Sets default values
AWayPoint::AWayPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CustomMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	TriggerBox->SetupAttachment(CustomMesh);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AWayPoint::OnBoxBeginOverlap);
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(CustomMesh);
}

// Called when the game starts or when spawned
void AWayPoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWayPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWayPoint::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFloatingVehicule* Car = Cast<AFloatingVehicule>(OtherActor);

	if (Car)
	{
		AAICarController* Controller = Cast<AAICarController>(Car->GetController());
		if (Car->CurrentWayPoint != this)
		{
			if (ShouldLockRotation && Car->IsA(AAICar::StaticClass()))
			{
				Car->GetBoxComponent()->BodyInstance.bLockZRotation = true;
				if (Cast<AAICar>(Car))
					Cast<AAICar>(Car)->CanTurn = false;
			}
			else
			{
				Car->GetBoxComponent()->BodyInstance.bLockZRotation = false;
				if (Cast<AAICar>(Car))
					Cast<AAICar>(Car)->CanTurn = true;
			}
			FVector Point = GetActorLocation();
			Point.Z -= 200;
			FRotator rotation = Arrow->GetComponentRotation();
			Car->SetRespawnPoint(Point, rotation);
			Car->CurrentWayPoint = this;
			if (IsLapCounter)
			{
				TArray<AActor*> FoundActors;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWayPoint::StaticClass(), FoundActors);
				if (Car->NumbWayPointsPassed >= FoundActors.Num() - 10)
				{
					
					Car->NumbWayPointsPassed = 0;
					Car->CurrentLap++;
				}
			}
			Car->NumbWayPointsPassed++;
		}
		if (ShouldResetPlayerRotation && Car->IsA(AAICar::StaticClass()))
		{
			AAICar* AICar = Cast<AAICar>(Car);
			if (AICar)
			{
				AICar->NewRotation = Arrow->GetComponentRotation();
				AICar->ShouldRotate = true;
			}
		}
		else
		{
			AAICar* AICar = Cast<AAICar>(Car);
			if(AICar)
				AICar->ShouldRotate = false;
		}
		if (ShouldBoost)
		{
			Car->ApplyBoost(1000000);
			Car->GetBoxComponent()->AddForce(Car->GetActorUpVector() * 1000000);
		}
	}
}