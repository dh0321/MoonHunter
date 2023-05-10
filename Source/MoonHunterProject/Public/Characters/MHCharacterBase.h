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


//Combo Action Section
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMHComboActionData> ComboActionData;
	
	void ProcessComboCommand();

	void ComboActionBegin(); //몽타주가 시작될 때 호출
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded); //몽타주가 모두 종료되었을 때 호출
	void SetComboCheckTimer();
	void ComboCheck();

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool HasNextComboCommand = false;

};
