// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AICarController.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API AAICarController : public AAIController
{
	GENERATED_BODY()
public:

	AAICarController(FObjectInitializer const& object_initializer);
	void BeginPlay() override;
	void OnPossess(APawn* const pawn) override;

	class UBlackboardComponent* get_blackboard();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behavior_treeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* btree;

class UBlackboardComponent* blackboard;
};
