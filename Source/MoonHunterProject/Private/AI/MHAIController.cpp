// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MHAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/MHAI.h"

AMHAIController::AMHAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_MHCharacter.BB_MHCharacter'"));
	if (nullptr != BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_MHCharacter.BT_MHCharacter'"));
	if (nullptr != BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}

}

void AMHAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());

		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}

}

void AMHAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AMHAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();

}
