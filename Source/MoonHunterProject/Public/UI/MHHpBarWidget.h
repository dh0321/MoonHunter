// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MHUserWidget.h"
#include "GameData/MHCharacterStat.h"
#include "MHHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOONHUNTERPROJECT_API UMHHpBarWidget : public UMHUserWidget
{
	GENERATED_BODY()
	
public:

	UMHHpBarWidget(const FObjectInitializer& ObjectInitializer);;

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateStat(const FMHCharacterStat& BaseStat, const FMHCharacterStat& ModifierStat);
	void UpdateHpBar(float NewCurrentHp);
	FString GetHpStatText();

protected:

	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	TObjectPtr<class UTextBlock> HpStat;

	UPROPERTY()
	float CurrentHp;


	UPROPERTY()
	float MaxHp;

	
};
