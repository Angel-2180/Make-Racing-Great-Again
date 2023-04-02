// Fill out your copyright notice in the Description page of Project Settings.

#include "EMP.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "../HoverTech/FloatingVehicule.h"
//include projectile component
#include "GameFramework/ProjectileMovementComponent.h"

AEMP::AEMP()
{
    if (!CollisionBox)
    {
        CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
        CollisionBox->OnComponentHit.AddDynamic(this, &AEMP::OnHit);
        CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AEMP::OnOverlapBegin);
        CollisionBox->SetBoxExtent(FVector(50.0f));
        CollisionBox->SetNotifyRigidBodyCollision(true);
        CollisionBox->SetCollisionProfileName(TEXT("Projectile"));
        CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
        CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
        RootComponent = CollisionBox;
    }

    if (!Mesh)
    {
        Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
        Mesh->SetRelativeLocation(FVector(0.0f));
        Mesh->SetRelativeRotation(FRotator(0.0f));
        Mesh->SetRelativeScale3D(FVector(3));
        Mesh->SetCollisionProfileName(TEXT("NoCollision"));
        Mesh->SetupAttachment(CollisionBox);
    }
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Workflow/3D/Meshs/bomb.bomb'"));
    if (MeshAsset.Succeeded())
    {
        Mesh->SetStaticMesh(MeshAsset.Object);
    }

    if (!ProjectileMovement)
    {
        ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
        ProjectileMovement->SetUpdatedComponent(CollisionBox);
        ProjectileMovement->InitialSpeed = 3250;
        ProjectileMovement->bRotationFollowsVelocity = true;
        ProjectileMovement->bShouldBounce = false;
        ProjectileMovement->bSimulationEnabled = true;
        ProjectileMovement->Friction = 0.0f;
        ProjectileMovement->Bounciness = 0.0f;
        ProjectileMovement->ProjectileGravityScale = 1.f;
    }
}

void AEMP::BeginPlay()
{
    AItem::BeginPlay();
    ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;
}

void AEMP::Tick(float DeltaTime)
{
    AItem::Tick(DeltaTime);
}

void AEMP::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && (OtherActor != this) && OtherComp && OtherActor->IsA(APawn::StaticClass()))
    {
        AFloatingVehicule* Player = Cast<AFloatingVehicule>(OtherActor);
        if (Player)
        {
            Player->isStun = true;
            Destroy();
        }
    }
}

void AEMP::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this))
    {
        if (OtherComp && OtherActor->IsA(APawn::StaticClass()))
        {
            AFloatingVehicule* Player = Cast<AFloatingVehicule>(OtherActor);
            if (Player)
            {
                Player->isStun = true;
                Destroy();
            }
        }
    }
}