// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerClass.h"
#include <string>
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../GreenShell.h"
#include "../Items/RedMushroom.h"
#include "Components/ArrowComponent.h"

// Sets default values
APlayerClass::APlayerClass()
{
    cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    pitchController = CreateDefaultSubobject<UPitchControl>(TEXT("Pitch Controller"));
    characterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character"));

    cameraBoom->SetupAttachment(RootComponent);
    followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);
    pitchController->SetupAttachment(RootComponent);
    pitchController->SetBoxComponent(hitbox);
    characterMesh->SetupAttachment(mesh);

    cameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character
    cameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller
    followCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void APlayerClass::BeginPlay()
{
    AFloatingVehicule::BeginPlay();
    playerController = Cast<APlayerController>(Controller);

    if (playerController)
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
            Subsystem->AddMappingContext(defaultMappingContext, 0);
    }

    lastGroundingState = isVehiculeGrounded;
}

// Called every frame
void APlayerClass::Tick(float DeltaTime)
{
    AFloatingVehicule::Tick(DeltaTime);

    isVehiculeGrounded = IsVehiculeGrounded();
    GroundingChange();
    pitchController->ControlPitch();
    RedressVehicule(DeltaTime);
    CameraEffects(DeltaTime);
}

// Called to bind functionality to input
void APlayerClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(steerAction, ETriggerEvent::Triggered, this, &APlayerClass::Steer);
        EnhancedInputComponent->BindAction(throttleAction, ETriggerEvent::Triggered, this, &APlayerClass::Throttle);
        EnhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &APlayerClass::LookBehind);
        EnhancedInputComponent->BindAction(useItemAction, ETriggerEvent::Triggered, this, &APlayerClass::UseItem);
    }
}

void APlayerClass::Steer(const FInputActionValue& axis)
{
    if (isStun)
        return;

    steeringVector = axis.Get<FVector>();

    steeringValue = steeringVector.X;

    const float heading = GetVelocity().Dot(GetActorForwardVector());

    if (heading < 0 && throttleVector.X < 0)
        hitbox->AddTorqueInDegrees(GetActorUpVector() * -steeringValue * maniability * 10000000);

    else
        hitbox->AddTorqueInDegrees(GetActorUpVector() * steeringValue * maniability * 10000000);

    if (isVehiculeGrounded)
        hitbox->AddTorqueInDegrees(GetActorForwardVector() * steeringValue * 1200000000);
}

void APlayerClass::Throttle(const FInputActionValue& axis)
{
    if (!isVehiculeGrounded || isStun)
        return;

    throttleVector = axis.Get<FVector>();

    if (throttleVector.X <= 0)
        throttleVector.X /= 1.5;

    Rumble(FMath::Abs(throttleVector.X));

    hitbox->AddForce(GetActorForwardVector() * throttleVector.X * motorStrenght * TerrainSpeedModifier());
}

void APlayerClass::LookBehind(const FInputActionValue& value)
{
    lookingBehind = !lookingBehind;

    cameraBoom->AddRelativeRotation({ 0,180,0 });

    if (lookingBehind)
        cameraBoom->TargetArmLength = 800.f;

    else
        cameraBoom->TargetArmLength = 400.f;
}

void APlayerClass::UseItem(const FInputActionValue& value)
{
    if (heldItem != nullptr)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector ForwardDirection = GetActorForwardVector();
        FVector SpawnLocation = GetActorLocation() + ForwardDirection;
        FRotator SpawnRotation = GetActorRotation();

        if (heldItem->Get()->GetName() == "GreenShell")
        {
            SpawnLocation = GetActorLocation() + ForwardDirection * 500;
        }
        else if (heldItem->Get()->GetName() == "EMP")
        {
            SpawnLocation = ItemLauncher->GetComponentLocation() + ItemLauncher->GetForwardVector() * 200;
            SpawnRotation = GetActorRotation() + FVector(60, 0, 0).Rotation();
        }

        this->GetWorld()->SpawnActor<AItem>(heldItem->Get(), SpawnLocation, SpawnRotation);

        heldItem = nullptr;
        ItemName = "None";
    }
}

void APlayerClass::Rumble(float value)
{
    const float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
    rumble += deltaTime;

    if (rumble < 0.3f)
        return;

    rumble = 0;

    playerController->PlayDynamicForceFeedback(value * (0.10f * (topLeftWheel->GetRumbleMultiplier() + bottomLeftWheel->GetRumbleMultiplier())), 0.25f, false, true, false, false);

    playerController->PlayDynamicForceFeedback(value * (0.10f * (topRightWheel->GetRumbleMultiplier() + topRightWheel->GetRumbleMultiplier())), 0.25f, false, false, false, true);
}

void APlayerClass::CameraEffects(float DeltaTime)

{
    speed = GetVelocity().Length();

    float cameraPitch = FMath::GetMappedRangeValueClamped(FVector2f{ 0.f,5000.f }, { -6.f,-30.f }, speed);

    float cameraCentrifuge = FMath::GetMappedRangeValueClamped(FVector2f{ 0.f, 5000.f }, { 1.f, 10.f }, speed);

    float cameraBacking = FMath::GetMappedRangeValueClamped(FVector2f{ 0.f, 5000.f }, { -200.f, -350.f }, speed);

    const FRotator rotation = FMath::RInterpTo(cameraBoom->GetRelativeRotation() - GetActorRotation(), { cameraPitch, cameraCentrifuge * steeringVector.X, 0 }, DeltaTime, 3);

    if (!lookingBehind)

        cameraBoom->SetRelativeRotation(GetActorRotation() + rotation);

    cameraBoom->SetRelativeLocation({ cameraBacking, 0, 85.f });
}

void APlayerClass::ApplyBoost(float BoostValue)

{
    hitbox->AddForce(GetActorForwardVector() * BoostValue * 1000);
}