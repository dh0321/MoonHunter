// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/MHAnimationAttackInterface.h"
#include "Interface/MHCharacterWidgetInterface.h"
#include "MHCharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};


UCLASS()
class MOONHUNTERPROJECT_API AMHCharacterBase : public ACharacter, public IMHAnimationAttackInterface, public IMHCharacterWidgetInterface
{
	GENERATED_BODY()

public:
	AMHCharacterBase();

	virtual void PostInitializeComponents() override;

//Swap Section
protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USkeletalMeshComponent> WolfMesh; 

	UPROPERTY(VisibleAnywhere, Category = Effect)
	TObjectPtr<class UNiagaraComponent> ChangeEffect;

	bool bIsWolf = false;

	void SwapCharacter();

	FORCEINLINE TObjectPtr<class USkeletalMeshComponent> GetCurrentMesh() 
	{
		return bIsWolf ? WolfMesh : GetMesh();
	}


protected:
	virtual void SetCharacterControlData(const class UMHCharacterControlData* CharacterControlData);

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UMHCharacterControlData*> CharacterControlManager;



//Combo Action Section
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> WolfComboActionMontage;

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


//Attack Hit Section
protected:
	virtual void AttackHitCheck() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


//Dead Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	virtual void SetDead();
	void PlayDeadAnimation();

	float DeadEventDelayTime = 3.0f;


//Stat Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMHCharacterStatComponent> Stat;	


//UI Widget Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMHWidgetComponent> HpBar;

	virtual void SetupCharacterWidget(UMHUserWidget* InUserWidget);


};
