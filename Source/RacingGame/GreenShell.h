// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Items/Item.h"
#include "GreenShell.generated.h"

UCLASS()
class RACINGGAME_API AGreenShell : public AItem
{
	GENERATED_BODY()

public:
	AGreenShell();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		class USceneComponent* root;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		class USphereComponent* sphereCollider;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UStaticMeshComponent* mesh;

	float speed = 2000.0f;

	bool onGround = false;
	float gravity;
	int MaxBounces = 5;
	int Bounces = 0;
};