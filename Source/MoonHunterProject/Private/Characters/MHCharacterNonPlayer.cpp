// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MHCharacterNonPlayer.h"

AMHCharacterNonPlayer::AMHCharacterNonPlayer()
{
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
