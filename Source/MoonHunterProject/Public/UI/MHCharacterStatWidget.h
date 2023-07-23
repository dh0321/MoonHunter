// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/MHCharacterStat.h"
#include "MHCharacterStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOONHUNTERPROJECT_API UMHCharacterStatWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
protected:
	virtual void NativeConstruct() override;
	
	
public:
	void UpdateStat(const FMHCharacterStat& BaseStat, const FMHCharacterStat& ModifierStat);
	

private:
	UPROPERTY()
	TMap<FName, class UTextBlock*> BaseLookup;

	UPROPERTY()
	TMap<FName, class UTextBlock*> ModifierLookup;

};
