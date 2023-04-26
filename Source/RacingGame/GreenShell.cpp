// Fill out your copyright notice in the Description page of Project Settings.

#include "GreenShell.h"
#include "Components/BoxComponent.h"
#include "HoverTech/FloatingVehicule.h"
#include "Components/SphereComponent.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AGreenShell::AGreenShell()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!root)
	{
		root = CreateDefaultSubobject<USceneComponent>("Root");
		RootComponent = root;
	}

	if (!sphereCollider)
	{
		sphereCollider = CreateDefaultSubobject<USphereComponent>("SphereCollision");
		sphereCollider->SetupAttachment(root);

		sphereCollider->SetNotifyRigidBodyCollision(true);
		sphereCollider->SetSimulatePhysics(true);
		sphereCollider->SetEnableGravity(false);

		// Query and physics

		sphereCollider->SetCollisionProfileName("BlockAllDynamic");
	}

	if (!mesh)
	{
		mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
		mesh->SetupAttachment(sphereCollider);

		mesh->SetCollisionProfileName("NoCollision");
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Workflow/3D/Meshs/Roue_Objet.Roue_Objet'"));
	if (meshAsset.Succeeded())
	{
		mesh->SetStaticMesh(meshAsset.Object);

		mesh->SetRelativeScale3D(FVector(4));
	}

	InitialLifeSpan = 15.f;
}

// Called when the game starts or when spawned
void AGreenShell::BeginPlay()
{
	Super::BeginPlay();

	if (sphereCollider)
		sphereCollider->OnComponentHit.AddDynamic(this, &AGreenShell::OnHit);

	gravity = sphereCollider->GetMass() * -GetWorld()->GetGravityZ();
	speed = 4000.0f;
}

void AGreenShell::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->IsA(APawn::StaticClass()))
		{
			AFloatingVehicule* Player = Cast<AFloatingVehicule>(OtherActor);
			if (Player)
			{
				Player->isStun = true;
				Destroy();
			}
		}
		else if (OtherActor->IsA(APawn::StaticClass()))
		{
			AItem* item = Cast<AItem>(OtherActor);
			if (item)
			{
				Destroy();
			}
		}
	}
}

// Called every frame
void AGreenShell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector forward = mesh->GetForwardVector();
	FVector right = mesh->GetRightVector();
	FVector down = mesh->GetUpVector() * -1;
	FVector normal;

	FHitResult hit;
	FCollisionQueryParams traceParams;
	traceParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(hit, mesh->GetComponentLocation(), mesh->GetComponentLocation() + down * (sphereCollider->GetScaledSphereRadius() + 0.1f), ECC_Visibility, traceParams))
	{
		normal = hit.ImpactNormal;
		onGround = true;
	}
	else
	{
		normal = FVector(0, 0, 1);
		onGround = false;
	}

	float yaw = mesh->GetComponentRotation().Yaw;
	float pitch = UKismetMathLibrary::MakeRotFromYZ(right, normal).Pitch;
	float roll = UKismetMathLibrary::MakeRotFromXZ(forward, normal).Roll;

	if (GetWorld()->LineTraceSingleByChannel(hit, mesh->GetComponentLocation(), mesh->GetComponentLocation() + forward * (sphereCollider->GetScaledSphereRadius() + 0.1f), ECC_Visibility, traceParams))
	{
		if (Cast<AItem>(hit.GetActor())) return;

		FVector direction = (mesh->GetComponentLocation() + forward) - mesh->GetComponentLocation();
		FVector mirror = UKismetMathLibrary::MirrorVectorByNormal(direction, hit.ImpactNormal);
		yaw = UKismetMathLibrary::MakeRotFromX(mirror).Yaw;
	}

	mesh->SetWorldRotation(FRotator(pitch, yaw, roll));
	forward = mesh->GetForwardVector();

	if (!onGround)
	{
		sphereCollider->AddForce(down * 980.0f, FName("None"), true);
	}
	else
	{
		sphereCollider->SetPhysicsLinearVelocity(FVector::Zero(), false);
	}

	sphereCollider->SetWorldLocation(sphereCollider->GetComponentLocation() + forward * speed * DeltaTime, false, nullptr, ETeleportType::TeleportPhysics);

	mesh->SetWorldLocation(sphereCollider->GetComponentLocation());
}