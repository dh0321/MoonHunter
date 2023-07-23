// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MHHUDWidget.h"
#include "Interface/MHCharacterHUDInterface.h"
#include "UI/MHHpBarWidget.h"
#include "UI/MHCharacterStatWidget.h"


UMHHUDWidget::UMHHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMHHUDWidget::UpdateStat(const FMHCharacterStat& BaseStat, const FMHCharacterStat& ModifierStat)
{
	FMHCharacterStat TotalStat = BaseStat + ModifierStat;
	HpBar->UpdateStat(BaseStat, ModifierStat);
	CharacterStat->UpdateStat(BaseStat, ModifierStat);
}

void UMHHUDWidget::UpdateHpBar(float NewCurrentHp)
{
	HpBar->UpdateHpBar(NewCurrentHp);
}

void UMHHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UMHHpBarWidget>(GetWidgetFromName(TEXT("WidgetHpBar")));
	ensure(HpBar);

	CharacterStat = Cast<UMHCharacterStatWidget>(GetWidgetFromName(TEXT("WidgetCharacterStat")));
	ensure(CharacterStat);

	IMHCharacterHUDInterface* HUDPawn = Cast<IMHCharacterHUDInterface>(GetOwningPlayerPawn());
	if (HUDPawn)
	{
		HUDPawn->SetupHUDWidget(this);
	}


}
