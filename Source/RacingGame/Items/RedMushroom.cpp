// Fill out your copyright notice in the Description page of Project Settings.

#include "RedMushroom.h"
#include "Components/SphereComponent.h"
#include "../HoverTech/FloatingVehicule.h"

// Sets default values
ARedMushroom::ARedMushroom()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //mesh
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Engine/EngineMeshes/Cylinder.Cylinder'"));

    if (MeshAsset.Succeeded())
    {
        Mesh->SetStaticMesh(MeshAsset.Object);
        Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        Mesh->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
        Mesh->SetCollisionProfileName(TEXT("NoCollision"));
    }

    if (!CollisionComponent)
    {
        CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
        CollisionComponent->InitSphereRadius(50.0f);
        CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
        CollisionComponent->SetNotifyRigidBodyCollision(true);
        CollisionComponent->SetGenerateOverlapEvents(true);
    }
    Mesh->SetupAttachment(CollisionComponent);
    RootComponent = CollisionComponent;

    SpeedUpAmount = 1000.0f;
}

// Called when the game starts or when spawned
void ARedMushroom::BeginPlay()
{
    AItem::BeginPlay();
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ARedMushroom::OnOverlapBegin);
}

void ARedMushroom::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    //debug
    
    if (OtherActor && OtherActor != this && OtherComponent && OtherActor->IsA(APawn::StaticClass()))
    {
        AFloatingVehicule* Player = Cast<AFloatingVehicule>(OtherActor);
        if (Player != nullptr)
        {
            Player->BoostingValue = SpeedUpAmount;
        }
        Destroy();
    }
}

// Called every frame
void ARedMushroom::Tick(float DeltaTime)
{
    AItem::Tick(DeltaTime);
}