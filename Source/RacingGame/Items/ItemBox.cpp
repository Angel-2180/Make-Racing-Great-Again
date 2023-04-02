// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBox.h"
#include "Item.h"
#include "RedMushroom.h"
#include "../GreenShell.h"
#include "Components/BoxComponent.h"
#include "../HoverTech/FloatingVehicule.h"
#include "EMP.h"
#include "TimerManager.h"
// Sets default values
AItemBox::AItemBox()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //~~~~~~~~~~~List of Items~~~~~~~~~~~~~~

    Items.Add(ARedMushroom::StaticClass());
    Items.Add(AGreenShell::StaticClass());
    Items.Add(AEMP::StaticClass());

    //~~~~~~~~~~~Constructor Code~~~~~~~~~~~~~~

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Workflow/3D/Meshs/crate_002.crate_002'"));
    if (MeshAsset.Succeeded())
    {
        Mesh->SetStaticMesh(MeshAsset.Object);
        Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        Mesh->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
        Mesh->SetCollisionProfileName(TEXT("NoCollision"));
    }

    if (!CollisionComponent)
    {
        CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
        CollisionComponent->InitBoxExtent(FVector(80.0f));
        CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
        CollisionComponent->SetNotifyRigidBodyCollision(true);
    }

    if (MeshModel)
    {
        Mesh->SetStaticMesh(MeshModel);
    }

    RootComponent = CollisionComponent;
    Mesh->SetupAttachment(CollisionComponent);
}

// Called when the game starts or when spawned
void AItemBox::BeginPlay()
{
    if (MeshModel)
        Mesh->SetStaticMesh(MeshModel);
    Super::BeginPlay();

    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemBox::OnOverlapBegin);
}

void AItemBox::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    int32 index = FMath::RandRange(0, Items.Num() - 1);

    if (OtherActor->IsA(APawn::StaticClass()))
    {
        AFloatingVehicule* pawn = Cast<AFloatingVehicule>(OtherActor);
        if (pawn && pawn->GetHeldItem() == nullptr)
        {
            pawn->GetHeldItem() = &Items[index];
            pawn->ItemName = Items[index]->GetName();
        }

        Disable();
    }
}

void AItemBox::Disable()
{
    //disable visibility
    Mesh->SetVisibility(false);

    //disable collision
    CollisionComponent->SetCollisionProfileName(TEXT("NoCollision"));

    GetWorldTimerManager().SetTimer(respawnTimer, this, &AItemBox::Enable, respawnTime, false);
}

void AItemBox::Enable()
{
    GetWorldTimerManager().ClearTimer(respawnTimer);

    //enable visibility
    Mesh->SetVisibility(true);

    //enable collision

    CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

// Called every frame
void AItemBox::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //rotate
    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += DeltaTime * 20.0f;
    SetActorRotation(NewRotation);

    //oscillate
    FVector NewLocation = GetActorLocation();
    oscillationValue += oscillationSpeed * DeltaTime;
    NewLocation.Z += oscillationAmplitude * (FMath::Sin(oscillationValue + DeltaTime) - FMath::Sin(oscillationValue));
    SetActorLocation(NewLocation);
}