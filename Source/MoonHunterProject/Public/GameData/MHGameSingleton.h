// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MHCharacterStat.h"
#include "MHGameSingleton.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMHGameSingleton, Error, All);

/**
 * 
 */
UCLASS()
class MOONHUNTERPROJECT_API UMHGameSingleton : public UObject
{
	GENERATED_BODY()
	
public:
	UMHGameSingleton();
	static UMHGameSingleton& Get();

//Character Stat Data Section
public:
	FORCEINLINE FMHCharacterStat GetCharacterStat(int32 InLevel) const { return CharacterStatTable.IsValidIndex(InLevel) ? CharacterStatTable[InLevel] : FMHCharacterStat(); }

	UPROPERTY()
	int32 CharacterMaxLevel;

private:
	TArray<FMHCharacterStat> CharacterStatTable;
	
	
};
