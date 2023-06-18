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
	return Stat->GetAttackRadius() * 2;
}

float AMHCharacterNonPlayer::GetAITurnSpeed()
{
	return 0.0f;
}
