// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatingVehicule.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
// Sets default values

AFloatingVehicule::AFloatingVehicule()
{
	PrimaryActorTick.bCanEverTick = true;

	CreateObjects();

	hitbox->InitBoxExtent({ 140, 50, 30 });

	hitbox->SetSimulatePhysics(true);

	hitbox->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	RootComponent = hitbox;

	SetupObjects();

	SetupTransforms();
}

UBoxComponent*& AFloatingVehicule::GetBoxComponent()
{
	return hitbox;
}

TSubclassOf<AItem>*& AFloatingVehicule::GetHeldItem()
{
	return heldItem;
}

// Called when the game starts or when spawned

void AFloatingVehicule::BeginPlay()
{
	Super::BeginPlay();
}

void AFloatingVehicule::CreateObjects()
{
	hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	topLeftWheel = CreateDefaultSubobject<UHoverWheel>(TEXT("Top Left Wheel"));
	topRightWheel = CreateDefaultSubobject<UHoverWheel>(TEXT("Top Right Wheel"));
	bottomLeftWheel = CreateDefaultSubobject<UHoverWheel>(TEXT("Bottom Left Wheel"));
	bottomRightWheel = CreateDefaultSubobject<UHoverWheel>(TEXT("Bottom Right Wheel"));
	ItemLauncher = CreateDefaultSubobject<USceneComponent>(TEXT("ItemLauncher"));
	EMPLaucherArrow1 = CreateDefaultSubobject<UArrowComponent>(TEXT("EMPArrodasdasdsw"));
}

void AFloatingVehicule::SetupObjects() const
{
	mesh->SetupAttachment(RootComponent);
	topLeftWheel->SetupAttachment(RootComponent);
	topRightWheel->SetupAttachment(RootComponent);
	bottomLeftWheel->SetupAttachment(RootComponent);
	bottomRightWheel->SetupAttachment(RootComponent);
	topLeftWheel->SetBoxComponent(hitbox);
	topRightWheel->SetBoxComponent(hitbox);
	bottomLeftWheel->SetBoxComponent(hitbox);
	bottomRightWheel->SetBoxComponent(hitbox);
	ItemLauncher->SetupAttachment(hitbox);
	EMPLaucherArrow1->SetupAttachment(ItemLauncher);
}

void AFloatingVehicule::SetupTransforms() const
{
	topLeftWheel->SetRelativeLocation({ 90.5f, -50.0f, -30.0f });
	topRightWheel->SetRelativeLocation({ 90.5f, 50.0f, -30.0f });
	bottomLeftWheel->SetRelativeLocation({ -90.5f, -50.0f, -30.0f });
	bottomRightWheel->SetRelativeLocation({ -90.5f, 50.0f, -30.0f });
	ItemLauncher->SetRelativeLocation({ 120, 0, 50 });
	EMPLaucherArrow1->SetRelativeLocation({ 0, 0, 0 });
	EMPLaucherArrow1->SetRelativeRotation({ 20,0,0 });
}

bool AFloatingVehicule::IsVehiculeGrounded()

{
	if (!topLeftWheel->IsWheelOnGround())
		return false;
	if (!topLeftWheel->IsWheelOnGround())
		return false;
	if (!topLeftWheel->IsWheelOnGround())
		return false;
	if (!topLeftWheel->IsWheelOnGround())
		return false;
	return true;
}

void AFloatingVehicule::RedressVehicule(float DeltaTime)
{
	if (isVehiculeGrounded)
		return;
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), { 0, GetActorRotation().Yaw, 0 }, DeltaTime, 1.5f));
}

void AFloatingVehicule::GroundingChange()
{
	if (lastGroundingState == isVehiculeGrounded)
		return;
	if (!isVehiculeGrounded)
		hitbox->SetLinearDamping(0.01);
	else
		hitbox->SetLinearDamping(1);

	lastGroundingState = isVehiculeGrounded;
}

float AFloatingVehicule::TerrainSpeedModifier() const
{
	return topLeftWheel->GetWheelTerrainConstraint() + topRightWheel->GetWheelTerrainConstraint() + bottomLeftWheel->GetWheelTerrainConstraint() + bottomRightWheel->GetWheelTerrainConstraint();
}

void AFloatingVehicule::SetRespawnPoint(FVector NewPoint, FRotator NewRotation)
{
	PointToRespawn = NewPoint;
	RotationToRespawn = NewRotation;
}

// Called every frame

void AFloatingVehicule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	isVehiculeGrounded = IsVehiculeGrounded();
	GroundingChange();
	RedressVehicule(DeltaTime);
	if (BoostingValue != 0)
		BoostingTimer(DeltaTime);
	if (isStun)
		StunTimer(DeltaTime);
	
}

void AFloatingVehicule::ApplyBoost(float BoostValue)
{
	hitbox->AddForce(GetActorForwardVector() * BoostValue * 1000);
}

void AFloatingVehicule::BoostingTimer(float DeltaTime)
{
	ApplyBoost(BoostingValue);
	BoostingTime += DeltaTime;
	if (BoostingTime >= MaxBoostingTime)
	{
		BoostingValue = 0;
		BoostingTime = 0.0f;
	}
}

void AFloatingVehicule::StunTimer(float DeltaTime)
{
	StunTime += DeltaTime;
	if (StunTime >= MaxStunTime)
	{
		isStun = false;
		StunTime = 0.0f;
	}
}