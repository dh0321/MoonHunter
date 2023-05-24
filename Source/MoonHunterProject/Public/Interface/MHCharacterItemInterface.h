// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHCharacterItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMHCharacterItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONHUNTERPROJECT_API IMHCharacterItemInterface
{
	GENERATED_BODY()

public:

	virtual void TakeItem(class UMHItemData* InItemData) = 0;
	

};
