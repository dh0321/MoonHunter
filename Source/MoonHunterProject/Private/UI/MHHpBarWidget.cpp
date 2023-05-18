// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MHHpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/MHCharacterWidgetInterface.h"

UMHHpBarWidget::UMHHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;
}

void UMHHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));
	ensure(HpProgressBar);

	IMHCharacterWidgetInterface* CharacterWidget = Cast<IMHCharacterWidgetInterface>(OwingActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}


}

void UMHHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	ensure(MaxHp > 0.0f);
	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(NewCurrentHp / MaxHp);
	}
}
