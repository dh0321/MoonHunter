// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MHCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOONHUNTERPROJECT_API UMHCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMHCharacterStatComponent();

protected:
	virtual void BeginPlay() override;

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;

	FORCEINLINE float GetMaxUp() { return MaxHp; }
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	//FORCEINLINE FMHCharacterStat GetTotalStat() const { return BaseStat + ModifierStat; }
	FORCEINLINE float GetAttackRadius() const { return AttackRadius; }
	float ApplyDamage(float InDamage);



protected:
	void SetHp(float NewHp);

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	float MaxHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	float AttackRadius;

		
};
