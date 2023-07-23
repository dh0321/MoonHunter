// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/MHCharacterStat.h"
#include "MHHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOONHUNTERPROJECT_API UMHHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMHHUDWidget(const FObjectInitializer& ObjectInitializer);
	
public:
	void UpdateStat(const FMHCharacterStat& BaseStat, const FMHCharacterStat& ModifierStat);
	void UpdateHpBar(float NewCurrentHp);


protected:
	virtual void NativeConstruct() override;


protected:
	UPROPERTY()
	TObjectPtr<class UMHHpBarWidget> HpBar;

	UPROPERTY()
	TObjectPtr<class UMHCharacterStatWidget> CharacterStat;



};
