// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MHCharacterBase.h"
#include "MHCharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class MOONHUNTERPROJECT_API AMHCharacterNonPlayer : public AMHCharacterBase
{
	GENERATED_BODY()
	
public:
	AMHCharacterNonPlayer();

protected:
	void SetDead() override;
	
};
