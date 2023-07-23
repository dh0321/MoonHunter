// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/MHItemData.h"
#include "MHWeaponItemData.generated.h"

/**
 * 
 */
UCLASS()
class MOONHUNTERPROJECT_API UMHWeaponItemData : public UMHItemData
{
	GENERATED_BODY()
	
public:
	UMHWeaponItemData();

	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("MHItemData", GetFName());
	}
	
	
public:
	UPROPERTY(EditAnywhere, Category = Weapon)
	TSoftObjectPtr<class USkeletalMesh> WeaponMesh;
	
	
	
};
