// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnVolume.h"
#include "Components/BoxComponent.h"

//Actor References
#include "../AI/AICar.h"

// Sets default values
ARespawnVolume::ARespawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ARespawnVolume::OnBoxBeginOverlap);
}

// Called when the game starts or when spawned
void ARespawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARespawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARespawnVolume::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAICar* Car = Cast<AAICar>(OtherActor);
	if (Car)
	{
		Car->Respawn();
	}
}