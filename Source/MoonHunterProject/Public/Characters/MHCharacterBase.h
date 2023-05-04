// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MHCharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};


UCLASS()
class MOONHUNTERPROJECT_API AMHCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMHCharacterBase();

protected:
	virtual void SetCharacterControlData(const class UMHCharacterControlData* CharacterControlData);

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UMHCharacterControlData*> CharacterControlManager;

};
