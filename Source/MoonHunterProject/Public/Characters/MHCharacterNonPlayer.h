// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MHCharacterBase.h"
#include "Interface/MHCharacterAIInterface.h"
#include "MHCharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class MOONHUNTERPROJECT_API AMHCharacterNonPlayer : public AMHCharacterBase, public IMHCharacterAIInterface
{
	GENERATED_BODY()
	
public:
	AMHCharacterNonPlayer();

protected:
	void SetDead() override;


//AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished);
	virtual void AttackByAI();

	FAICharacterAttackFinished OnAttackFinished;
	
	virtual void NotifyComboActionEnd() override;
};
