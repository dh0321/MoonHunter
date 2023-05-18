// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MHUserWidget.h"
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

	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrentHp);

protected:

	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	float MaxHp;

	
};
