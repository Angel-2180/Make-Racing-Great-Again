// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverWheel.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/BoxComponent.h"
#include "RacingGame/Player/PlayerClass.h"

UHoverWheel::UHoverWheel()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHoverWheel::BeginPlay()
{
	Super::BeginPlay();
	owner = Cast<APawn>(GetOwner());
	ignoredActors.Add(TArray<AActor*>::ElementType(this));
	ignoredActors.Add(owner);
}

void UHoverWheel::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	isGrounded = MakeHover();
}

void UHoverWheel::SetBoxComponent(UBoxComponent* comp)
{
	ownerBoxComponent = comp;
}

float UHoverWheel::GetWheelTerrainConstraint() const
{
	return wheelTerrainConstraint;
}

bool UHoverWheel::MakeHover()
{
	actorLocation = GetComponentLocation();

	UKismetSystemLibrary::LineTraceSingle(GetWorld(), actorLocation, actorLocation + (-GetUpVector() * traceLength),UEngineTypes::ConvertToTraceType(ECC_WorldStatic),
		false, ignoredActors, EDrawDebugTrace::None, result, true);

	if (result.GetActor() == nullptr)
		return false;

	const float alpha = (result.Location - GetComponentLocation()).Length();

	const float lerp = FMath::Lerp(hoverForce, 0.0f, alpha / traceLength);

	const FVector force = result.ImpactNormal * lerp;

	//

	if (result.GetActor()->ActorHasTag("ROAD") || result.GetActor()->ActorHasTag("LOOPING"))
		SetWheelTerrainConstraint(2500);

	else
		SetWheelTerrainConstraint(1000);

	ownerBoxComponent->AddForceAtLocation(force, GetComponentLocation());

	return true;
}

void UHoverWheel::SetWheelTerrainConstraint(float value)
{
	wheelTerrainConstraint = value;

	if (value > 2000)
		rumble = 0;

	else
		rumble = 1;
}

bool UHoverWheel::IsWheelOnGround() const
{
	return isGrounded;
}

short UHoverWheel::GetRumbleMultiplier() const
{
	return rumble;
}