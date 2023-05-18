// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHCharacterWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMHCharacterWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONHUNTERPROJECT_API IMHCharacterWidgetInterface
{
	GENERATED_BODY()

public:

	virtual void SetupCharacterWidget(class UMHUserWidget* InUserWidget) = 0;

};
