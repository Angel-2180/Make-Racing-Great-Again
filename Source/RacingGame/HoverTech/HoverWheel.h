// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Pawn.h"
#include "HoverWheel.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RACINGGAME_API UHoverWheel : public USceneComponent
{
	GENERATED_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	//	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HoverValues, meta = (AllowPrivateAccess = "true"))
		float traceLength = 80.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HoverValues, meta = (AllowPrivateAccess = "true"))
		float hoverForce = 20000.0f;

	APawn* owner;
	class UBoxComponent* ownerBoxComponent;

	TArray<AActor*> ignoredActors;
	FHitResult result;

	FVector actorLocation;

	float wheelTerrainConstraint; // makes the cars slower if the wheel is over the grass
	short rumble;
	bool isGrounded;

	bool MakeHover();
	void SetWheelTerrainConstraint(float value);

public:	

	UHoverWheel();

protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetBoxComponent(class UBoxComponent* comp);

	float GetWheelTerrainConstraint() const;

	bool IsWheelOnGround() const;

	short GetRumbleMultiplier() const;
};