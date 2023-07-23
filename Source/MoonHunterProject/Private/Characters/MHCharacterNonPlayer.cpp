// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MHCharacterNonPlayer.h"
#include "Engine/AssetManager.h"
#include "AI/MHAIController.h"
#include "CharacterStat/MHCharacterStatComponent.h"

AMHCharacterNonPlayer::AMHCharacterNonPlayer()
{
	AIControllerClass = AMHAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMHCharacterNonPlayer::SetDead()
{
	Super::SetDead();

	AMHAIController* MHAIController = Cast<AMHAIController>(GetController());
	if (MHAIController)
	{
		MHAIController->StopAI();
	}


	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);

}

float AMHCharacterNonPlayer::GetAIPatrolRadius()
{
	return 800.0f;
}

float AMHCharacterNonPlayer::GetAIDetectRange()
{
	return 400.0f;
}

float AMHCharacterNonPlayer::GetAIAttackRange()
{
	return Stat->GetTotalStat().AttackRange + Stat->GetAttackRadius() * 2;
}

float AMHCharacterNonPlayer::GetAITurnSpeed()
{
	return 2.0f;
}

void AMHCharacterNonPlayer::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void AMHCharacterNonPlayer::AttackByAI()
{
	ProcessComboCommand();
}

void AMHCharacterNonPlayer::NotifyComboActionEnd()
{
	Super::NotifyComboActionEnd();
	OnAttackFinished.ExecuteIfBound();
}
