// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "HoverWheel.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "RacingGame/Items/Item.h"
#include "FloatingVehicule.generated.h"

UCLASS()
class RACINGGAME_API AFloatingVehicule : public APawn
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Hitbox, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* hitbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wheels, meta = (AllowPrivateAccess = "true"))
		UHoverWheel* topLeftWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wheels, meta = (AllowPrivateAccess = "true"))
		UHoverWheel* topRightWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wheels, meta = (AllowPrivateAccess = "true"))
		UHoverWheel* bottomLeftWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wheels, meta = (AllowPrivateAccess = "true"))
		UHoverWheel* bottomRightWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VehiculeValues, meta = (AllowPrivateAccess = "true"))
		float maniability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VehiculeValues, meta = (AllowPrivateAccess = "true"))
		float motorStrenght;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VehiculeValues, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* ItemLauncher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VehiculeValues, meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* EMPLaucherArrow1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float speed;

	bool isVehiculeGrounded;
	bool lastGroundingState;
	float BoostingTime = 0.0f;
	float StunTime = 0.0f;

	TSubclassOf<AItem>* heldItem;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug, meta = (AllowPrivateAccess = "true"))
		FString ItemName = "None";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations, meta = (AllowPrivateAccess = "true"))
		bool isStun = false;

	int MaxStunTime = 2;
	int MaxBoostingTime = 5;
	float BoostingValue = 0;

	// Sets default values for this pawn's properties

	AFloatingVehicule();

	UBoxComponent*& GetBoxComponent();
	TSubclassOf<AItem>*& GetHeldItem();
	USceneComponent* GetEMPLauncher() { return ItemLauncher; };
	UArrowComponent* GetEMPLauncherArrow() { return EMPLaucherArrow1; };
    bool IsVehiculeGrounded();

	//RESPAWNING

	FVector PointToRespawn;
	FRotator RotationToRespawn;
	void SetRespawnPoint(FVector NewPoint, FRotator NewRotation);
	class AWayPoint* CurrentWayPoint;
	int NumbWayPointsPassed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laps")
		int CurrentLap = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laps")
		int CurrentPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laps")
		int TotalLaps = 3;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    void CreateObjects();
    void SetupObjects() const;
    void SetupTransforms() const;
    void RedressVehicule(float DeltaTime);
    void GroundingChange();
    float TerrainSpeedModifier() const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void ApplyBoost(float BoostValue);

private:
	void BoostingTimer(float DeltaTime);
	void StunTimer(float DeltaTime);
};