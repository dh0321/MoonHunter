// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/MHItemData.h"
#include "MHPotionItemData.generated.h"

/**
 * 
 */
UCLASS()
class MOONHUNTERPROJECT_API UMHPotionItemData : public UMHItemData
{
	GENERATED_BODY()
	
public:
	UMHPotionItemData();

	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("MHItemData", GetFName());
	}


public:
	UPROPERTY(EditAnywhere, Category = Hp)
	float HealAmount;
	
};
