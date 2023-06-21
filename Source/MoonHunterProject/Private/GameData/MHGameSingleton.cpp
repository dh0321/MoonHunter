// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/MHGameSingleton.h"

DEFINE_LOG_CATEGORY(LogMHGameSingleton);

UMHGameSingleton::UMHGameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DataTableRef(TEXT("/Script/Engine.DataTable'/Game/GameData/MHCharacterStatTable.MHCharacterStatTable'"));
	if (nullptr != DataTableRef.Object)
	{
		const UDataTable* DataTable = DataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);
	
		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, CharacterStatTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FMHCharacterStat*>(Value);
			}
		);
	
		CharacterMaxLevel = CharacterStatTable.Num();
		ensure(CharacterMaxLevel > 0);
	
	}
}

UMHGameSingleton& UMHGameSingleton::Get()
{
	UMHGameSingleton* Singleton = CastChecked<UMHGameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}

	UE_LOG(LogMHGameSingleton, Error, TEXT("Invalid Game Singleton"));
	return *NewObject<UMHGameSingleton>();


}
