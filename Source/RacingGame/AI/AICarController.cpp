// Fill out your copyright notice in the Description page of Project Settings.


#include "AICarController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
AAICarController::AAICarController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_AICar.BT_AICar'"));
	if (obj.Succeeded())
	{
		btree = obj.Object;
	}
	behavior_treeComponent = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void AAICarController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(btree);
	behavior_treeComponent->StartTree(*btree);
}

void AAICarController::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	if (blackboard)
	{
		blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}
}

UBlackboardComponent* AAICarController::get_blackboard()
{
	return blackboard;
}
