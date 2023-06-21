
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MHCharacterStat.generated.h"

USTRUCT(BlueprintType)
struct FMHCharacterStat : public FTableRowBase
{
	GENERATED_BODY()

public:
	FMHCharacterStat() : MaxHp(0.0f), Attack(0.0f), AttackRange(0.0f), AttackSpeed(0.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		float MovementSpeed;

	FMHCharacterStat operator+(const FMHCharacterStat& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FMHCharacterStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 StatNum = sizeof(FMHCharacterStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}
};