// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MHComboActionData.generated.h"

/**
 * 
 */
UCLASS()
class MOONHUNTERPROJECT_API UMHComboActionData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
	
public:
	UMHComboActionData();

	UPROPERTY(EditAnywhere, Category = Name)
	FString MontageSectionNamePrefix;

	UPROPERTY(EditAnywhere, Category = Name)
	uint8 MaxComboCount; //몇 개의 콤보 액션이 있는지

	UPROPERTY(EditAnywhere, Category = Name)
	float FrameRate;

	UPROPERTY(EditAnywhere, Category = Name)
	TArray<float> EffectiveFrameCount; //입력이 사전에 입력됐는지 감지하는 프레임 지정


};
