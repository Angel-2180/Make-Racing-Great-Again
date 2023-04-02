// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PitchControl.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RACINGGAME_API UPitchControl : public USceneComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PitchValues, meta = (AllowPrivateAccess = "true"))
		float traceLength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PitchValues, meta = (AllowPrivateAccess = "true"))
		float hoverForce;

	APawn* owner;
	class UBoxComponent* ownerBoxComponent;

	TArray<AActor*> ignoredActors;
	FHitResult result;

	FVector actorLocation;

	// Sets default values for this component's properties
	UPitchControl();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetBoxComponent(UBoxComponent* comp);
	void ControlPitch();
};