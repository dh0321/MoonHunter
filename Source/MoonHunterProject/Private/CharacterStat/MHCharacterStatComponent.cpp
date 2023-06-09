// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/MHCharacterStatComponent.h"
#include "GameData/MHGameSingleton.h"

UMHCharacterStatComponent::UMHCharacterStatComponent()
{
	CurrentLevel = 1;
	AttackRadius = 50.0f;
}


void UMHCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetLevelStat(CurrentLevel);
	SetHp(BaseStat.MaxHp);
	
}

void UMHCharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, UMHGameSingleton::Get().CharacterMaxLevel);
	BaseStat = UMHGameSingleton::Get().GetCharacterStat(CurrentLevel);
	check(BaseStat.MaxHp > 0.0f);
}

float UMHCharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}

	return 0.0f;
}

void UMHCharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, BaseStat.MaxHp);

	OnHpChanged.Broadcast(CurrentHp);



}




