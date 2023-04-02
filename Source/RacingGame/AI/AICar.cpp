// Fill out your copyright notice in the Description page of Project Settings.


#include "AICar.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "RacingGame/HoverTech/HoverWheel.h"
#include "RacingGame/HoverTech/PitchControl.h"
#include "Perception/PawnSensingComponent.h"
//Temporarily
#include "AICarController.h"
#include "bbKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RacingGame/HoverTech/PitchControl.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
AAICar::AAICar()
{
	PrimaryActorTick.bStartWithTickEnabled = true;

	PerceptionTest = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Perception Comp"));

	pitchController = CreateDefaultSubobject<UPitchControl>(TEXT("pitch Comp"));

	pitchController->SetupAttachment(RootComponent);
	pitchController->SetBoxComponent(hitbox);
}

void AAICar::BeginPlay()
{
	Super::BeginPlay();
	PerceptionTest->OnSeePawn.AddDynamic(this, &AAICar::OnSeePawn);
	SetRespawnPoint(GetActorLocation(), GetActorRotation());
}

void AAICar::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	isVehiculeGrounded = IsVehiculeGrounded();
	GroundingChange();

	pitchController->ControlPitch();
	RedressVehicule(DeltaSeconds);
	CheckGround();


		
}

void AAICar::Steer(FVector direction) const
{
	hitbox->AddTorqueInDegrees({ 0, 0, direction.X * maniability * 50000000 });
}

void AAICar::Throttle(float Amount) const
{
	if (Amount <= 0)
		Amount /= 1.5;

	FVector ThrottleVec = GetActorForwardVector();
	ThrottleVec.Z = 0;

	hitbox->AddForce(GetActorForwardVector() * Amount * motorStrenght * 10000); // Get 90 vector from ground
}

void AAICar::OnSeePawn(APawn* OtherPawn)
{
	if (!std::count(PawnsInMemory.begin(), PawnsInMemory.end(), OtherPawn))
	{
		PawnsInMemory.emplace_back(OtherPawn);
	}
}

bool AAICar::CheckSeeingPawn(const APawn* pawn) const
{
	if (!pawn || !PerceptionTest)
		return false;

	return PerceptionTest->HasLineOfSightTo(pawn) && FVector::Distance(GetActorLocation(), pawn->GetActorLocation()) < 600;
}

void AAICar::CheckGround()
{
	FVector EndDown = GetActorLocation() - (GetActorUpVector() * 300);
	FHitResult OutHit;

	FCollisionQueryParams CollisionParams = FCollisionQueryParams();
	CollisionParams.AddIgnoredActor(this);
	AAICarController* controller = Cast<AAICarController>(GetController());

	
	if (GetWorld()->LineTraceSingleByObjectType(OutHit, GetActorLocation(), EndDown, FCollisionObjectQueryParams::AllObjects, CollisionParams))
	{
		FString name = OutHit.GetActor()->GetName();

		if (OutHit.GetActor()->ActorHasTag(FName("LOOP")))
		{
			pitchController->ControlPitch();
			controller->get_blackboard()->SetValueAsBool(bbKeys::Loop, true);
			return;
		}
		else if (OutHit.GetActor()->ActorHasTag(FName("TERRAIN")))
		{
			CurrentTimeWithoutGround = 0;
			controller->get_blackboard()->SetValueAsBool(bbKeys::Loop, false);
			if (ShouldRotate)
			{
				if (CurrentAlpha >= 0.99f)
				{
					ShouldRotate = false;
				}
				LerpRotation(CurrentAlpha);
				CurrentAlpha += RotationSpeed * GetWorld()->GetDeltaSeconds();
			}
			else
				CurrentAlpha = 0;

			return;
		}
		controller->get_blackboard()->SetValueAsBool(bbKeys::Loop, false);
	}
	PushToGround();
	CurrentAlpha = 0;
}

void AAICar::PushToGround()
{
	hitbox->SetAllPhysicsLinearVelocity(FVector(0, 0, GetVelocity().Z));
	CurrentTimeWithoutGround += GetWorld()->GetDeltaSeconds();

	FVector ThrottleVec = FVector(0, 0, -1);

	//hitbox->AddForce(ThrottleVec * 1000000);
}


void AAICar::Respawn()
{
	hitbox->AddForce({ 0,0,0 });
	SetActorLocation(PointToRespawn);
	SetActorRotation(RotationToRespawn);
}

void AAICar::LerpRotation(float Alpha)
{
	FRotator NewRot = FRotator(FQuat::Slerp(GetActorRotation().Quaternion(), NewRotation.Quaternion(), Alpha));

	SetActorRotation(NewRot);
}
