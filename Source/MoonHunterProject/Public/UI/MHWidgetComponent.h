// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "MHWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class MOONHUNTERPROJECT_API UMHWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
protected:
	virtual void InitWidget() override;

	
};
