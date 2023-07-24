// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/MHAnimationAttackInterface.h"
#include "Interface/MHCharacterWidgetInterface.h"
#include "Interface/MHCharacterItemInterface.h"
#include "GameData/MHCharacterStat.h"
#include "MHCharacterBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMHCharacter, Log, All);

UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};

DECLARE_DELEGATE_OneParam(FOnTakeItemDelegate, class UMHItemData* /*InItemData*/);
USTRUCT(BlueprintType)
struct FTakeItemDelegateWrapper
{
	GENERATED_BODY()
	FTakeItemDelegateWrapper() {}
	FTakeItemDelegateWrapper(const FOnTakeItemDelegate& InItemDelegate) : ItemDelegate(InItemDelegate) {}
	FOnTakeItemDelegate ItemDelegate;
};


UCLASS()
class MOONHUNTERPROJECT_API AMHCharacterBase : public ACharacter, public IMHAnimationAttackInterface, public IMHCharacterWidgetInterface, public IMHCharacterItemInterface
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

	UPROPERTY(VisibleAnywhere, Category = Character)
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> WolfComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMHComboActionData> ComboActionData;
	
	void ProcessComboCommand();

	void ComboActionBegin(); //몽타주가 시작될 때 호출
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded); //몽타주가 모두 종료되었을 때 호출
	virtual void NotifyComboActionEnd();
	void SetComboCheckTimer();
	void ComboCheck();

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool HasNextComboCommand = false;


//Attack Hit Section
protected:
	virtual void AttackHitCheck() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


// Hit Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> PersonHitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> WolfHitMontage;

	void PlayHitAnimation();


//Dead Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> WolfDeadMontage;

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



//Item Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> Weapon;
	
	UPROPERTY()
	TArray<FTakeItemDelegateWrapper> TakeItemActions;	

	virtual void TakeItem(class UMHItemData* InItemData) override;
	virtual void EquipWeapon(class UMHItemData* InItemData);
	virtual void DrinkPotion(class UMHItemData* InItemData);
	virtual void ReadScroll(class UMHItemData* InItemData);


//Stat Section
public:
	void ApplyStat(const FMHCharacterStat& BaseStat, const FMHCharacterStat& ModifierStat);

};