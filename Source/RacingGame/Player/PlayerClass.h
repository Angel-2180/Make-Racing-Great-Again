// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "RacingGame/HoverTech/HoverWheel.h"
#include "RacingGame/HoverTech/PitchControl.h"
#include "../Items/Item.h"
#include "../HoverTech/FloatingVehicule.h"
#include "PlayerClass.generated.h"

UCLASS()
class RACINGGAME_API APlayerClass : public AFloatingVehicule
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* cameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* followCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* defaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* steerAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* throttleAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* lookAction;

	/** UseItem Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* useItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wheels, meta = (AllowPrivateAccess = "true"))
		UPitchControl* pitchController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* characterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		float steeringValue;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	APlayerController* playerController; // For Controller rumble

	FVector look;
	FVector steeringVector;
	FVector throttleVector;
	FRotator lastRotation;
	FRotator newRotation;

	float rumble;

	bool lookingBehind = false;

public:

	// Sets default values for this pawn's properties
	APlayerClass();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Steer(const FInputActionValue& axis);

	void Throttle(const FInputActionValue& axis);

	void LookBehind(const FInputActionValue& value);

	void UseItem(const FInputActionValue& value);

	void Rumble(float value);

	void CameraEffects(float DeltaTime);

public:
	void ApplyBoost(float BoostValue) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};