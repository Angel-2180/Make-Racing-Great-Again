// Fill out your copyright notice in the Description page of Project Settings.


#include "Loop.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
// Sets default values
ALoop::ALoop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALoop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALoop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

