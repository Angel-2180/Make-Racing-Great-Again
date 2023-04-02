// Fill out your copyright notice in the Description page of Project Settings.

#include "PitchControl.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UPitchControl::UPitchControl()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UPitchControl::BeginPlay()
{
	Super::BeginPlay();

	owner = Cast<APawn>(GetOwner());
	ignoredActors.Add(TArray<AActor*>::ElementType(this));
	ignoredActors.Add(owner);
}

void UPitchControl::SetBoxComponent(UBoxComponent* comp)
{
	ownerBoxComponent = comp;
}

// Called every frame
void UPitchControl::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//ControlPitch();
}

void UPitchControl::ControlPitch()
{

	actorLocation = GetComponentLocation();

	UKismetSystemLibrary::LineTraceSingle(GetWorld(), actorLocation, actorLocation + (-GetUpVector() * traceLength), UEngineTypes::ConvertToTraceType(ECC_WorldStatic),
		false, ignoredActors, EDrawDebugTrace::None, result, true);

	if (!result.GetActor()) return;

	if (!result.GetActor()->ActorHasTag("LOOPING")) return;

	const float alpha = (result.Location - GetComponentLocation()).Length();

	const float lerp = FMath::Lerp(hoverForce, 0.0f, traceLength / alpha);

	ownerBoxComponent->AddTorqueInDegrees(owner->GetActorRightVector() * lerp);
}