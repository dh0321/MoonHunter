// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MHCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/MHCharacterControlData.h"
#include "Animation/AnimMontage.h"
#include "Characters/MHComboActionData.h"
#include "Physics/MHCollision.h"
#include "Engine/DamageEvents.h"
#include "CharacterStat/MHCharacterStatComponent.h"
#include "UI/MHWidgetComponent.h"
#include "UI/MHHpBarWidget.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Item/MHWeaponItemData.h"
#include "Item/MHPotionItemData.h"

DEFINE_LOG_CATEGORY(LogMHCharacter);

AMHCharacterBase::AMHCharacterBase()
{
 	//Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_MHCAPSULE);

	//Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	//Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -100.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	//WolfMesh
	WolfMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WolfMesh"));
	WolfMesh->SetupAttachment(GetCapsuleComponent());
	WolfMesh->SetHiddenInGame(true);
	WolfMesh->Deactivate();

	
	//Person
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Game/Assets/FOX/Mesh/SK_fox.SK_fox"));
	if (CharacterMeshRef.Object)
	{
		/*auto Comp = FindComponentByClass<USkeletalMeshComponent>();
		Comp->SetSkeletalMesh(CharacterMeshRef.Object);*/

		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/Animations/AnimBlueprints/ABP_Person.ABP_Person_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}


	//Wolf
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WolfCharacterMeshRef(TEXT("/Game/Assets/Cats_pack/Cats/SimpleCat/Meshes/Mesh_Cat_Simple.Mesh_Cat_Simple"));
	if (WolfCharacterMeshRef.Object)
	{
		WolfMesh->SetSkeletalMesh(WolfCharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> WolfAnimInstanceClassRef(TEXT("/Game/Animations/AnimBlueprints/ABP_CatSimple_2.ABP_CatSimple_2_C"));
	if (WolfAnimInstanceClassRef.Class)
	{
		WolfMesh->SetAnimInstanceClass(WolfAnimInstanceClassRef.Class);
	}


	//Data
	static ConstructorHelpers::FObjectFinder<UMHCharacterControlData> ShoulderDataRef(TEXT("/Game/CharacterControl/MHC_Shoulder.MHC_Shoulder"));
	if (ShoulderDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Shoulder, ShoulderDataRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMHCharacterControlData> QuaterDataRef(TEXT("/Game/CharacterControl/MHC_Quater.MHC_Quater"));
	if (QuaterDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Quater, QuaterDataRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMHComboActionData> ComboActionDataRef(TEXT("/Game/CharacterAction/MHA_ComboAttack.MHA_ComboAttack"));
	if (ComboActionDataRef.Object)
	{
		ComboActionData = ComboActionDataRef.Object;
	}


	//Animations
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Game/Animations/AnimMontage/AM_PersonComboAttack.AM_PersonComboAttack"));
	if (ComboActionMontageRef.Object)
	{
		ComboActionMontage = ComboActionMontageRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Game/Animations/AnimMontage/AM_Dead.AM_Dead"));
	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> WolfComboActionMontageRef(TEXT("/Game/Animations/AnimMontage/AM_CatSimpleComboAttack.AM_CatSimpleComboAttack"));
	if (WolfComboActionMontageRef.Object)
	{
		WolfComboActionMontage = WolfComboActionMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> WolfDeadMontageRef(TEXT("/Game/Animations/AnimMontage/AM_CatSimpleDead.AM_CatSimpleDead"));
	if (WolfDeadMontageRef.Object)
	{
		WolfDeadMontage = WolfDeadMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PersonHitMontageRef(TEXT("/Game/Animations/AnimMontage/AM_PersonHit.AM_PersonHit"));
	if (PersonHitMontageRef.Object)
	{
		PersonHitMontage = PersonHitMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> WolfHitMontageRef(TEXT("/Game/Animations/AnimMontage/AM_CatSimpleHit.AM_CatSimpleHit"));
	if (WolfHitMontageRef.Object)
	{
		WolfHitMontage = WolfHitMontageRef.Object;
	}


	//Stat Component
	Stat = CreateDefaultSubobject<UMHCharacterStatComponent>(TEXT("Stat"));

	//Widget Component
	HpBar = CreateDefaultSubobject<UMHWidgetComponent>(TEXT("Widget"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 210.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWidgetRef(TEXT("/Game/UI/WBP_HpBar.WBP_HpBar_C"));
	if (HpBarWidgetRef.Class)
	{
		HpBar->SetWidgetClass(HpBarWidgetRef.Class);
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetDrawSize(FVector2D(150.f, 15.0f));
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	//Niagara Effect
	ChangeEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ChangeEffect"));
	ChangeEffect->SetupAttachment(GetCapsuleComponent());
	ChangeEffect->bAutoActivate = false;

	//Item Actions
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &AMHCharacterBase::EquipWeapon)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &AMHCharacterBase::DrinkPotion)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &AMHCharacterBase::ReadScroll)));

	//Weapon Component
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));

}

void AMHCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Stat->OnHpZero.AddUObject(this, &AMHCharacterBase::SetDead);
	Stat->OnStatChanged.AddUObject(this, &AMHCharacterBase::ApplyStat);
}

void AMHCharacterBase::SetCharacterControlData(const UMHCharacterControlData* CharacterControlData)
{
	//Pawn
	bUseControllerRotationYaw = CharacterControlData->bUseControllerRotationYaw;

	//CharacterMovement
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;

}

void AMHCharacterBase::SwapCharacter()
{
	ChangeEffect->Activate(true);

	if (bIsWolf)
	{
		GetMesh()->Activate();
		WolfMesh->Deactivate();
		GetMesh()->SetHiddenInGame(false);
		WolfMesh->SetHiddenInGame(true);
		GetCharacterMovement()->MaxWalkSpeed = 650.f;
		GetCharacterMovement()->JumpZVelocity = 600.f;
		GetCharacterMovement()->AirControl = 0.35f;
		HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 210.0f));
	}
	else
	{
		GetMesh()->Deactivate();
		WolfMesh->Activate();
		GetMesh()->SetHiddenInGame(true);
		WolfMesh->SetHiddenInGame(false);
		GetCharacterMovement()->MaxWalkSpeed = 650.f;
		GetCharacterMovement()->JumpZVelocity = 490.f;
		GetCharacterMovement()->AirControl = 0.35f;
		HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));

	}

	bIsWolf = !bIsWolf;
}

void AMHCharacterBase::ProcessComboCommand()
{
	if (CurrentCombo == 0)
	{
		ComboActionBegin();
		return;
	}

	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = false;
	}
	else
	{
		HasNextComboCommand = true;
	}
	 
}

void AMHCharacterBase::ComboActionBegin()
{
	//Combo Status
	CurrentCombo = 1;

	//Movement Setting
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	//Animation Setting
	const float AttackSpeedRate = Stat->GetTotalStat().AttackSpeed;
	UAnimInstance* AnimInstance = GetCurrentMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(bIsWolf ? WolfComboActionMontage : ComboActionMontage, AttackSpeedRate);


	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &AMHCharacterBase::ComboActionEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, bIsWolf ? WolfComboActionMontage : ComboActionMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();

}

void AMHCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	ensure(CurrentCombo != 0);
	CurrentCombo = 0;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	NotifyComboActionEnd();
}

void AMHCharacterBase::NotifyComboActionEnd()
{
}

void AMHCharacterBase::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	const float AttackSpeedRate = Stat->GetTotalStat().AttackSpeed;
	float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate) / AttackSpeedRate;

	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AMHCharacterBase::ComboCheck, ComboEffectiveTime, false);
	}

}

void AMHCharacterBase::ComboCheck()
{
	ComboTimerHandle.Invalidate();
	if (HasNextComboCommand)
	{
		UAnimInstance* AnimInstance = GetCurrentMesh()->GetAnimInstance();

		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionNamePrefix, CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);
		SetComboCheckTimer();
		HasNextComboCommand = false;
	}
}

void AMHCharacterBase::AttackHitCheck()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const float AttackRange = Stat->GetTotalStat().AttackRange;
	const float AttackRadius = Stat->GetAttackRadius();
	const float AttackDamage = Stat->GetTotalStat().Attack;
	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CCHANNEL_MHACTION, FCollisionShape::MakeSphere(AttackRadius), Params);
	if (HitDetected)
	{
		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
	}

#if ENABLE_DRAW_DEBUG

	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);

#endif

}

float AMHCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	PlayHitAnimation();
	Stat->ApplyDamage(DamageAmount);
	
	return DamageAmount;
}

void AMHCharacterBase::PlayHitAnimation()
{
	UAnimInstance* AnimInstance = GetCurrentMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(bIsWolf ? WolfHitMontage : PersonHitMontage, 1.0f);
}

void AMHCharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);
	HpBar->SetHiddenInGame(true);
}

void AMHCharacterBase::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetCurrentMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(bIsWolf ? WolfDeadMontage : DeadMontage, 1.0f);

}

void AMHCharacterBase::SetupCharacterWidget(UMHUserWidget* InUserWidget)
{
	UMHHpBarWidget* HpBarWidget = Cast<UMHHpBarWidget>(InUserWidget);
	if (HpBarWidget)
	{
		HpBarWidget->UpdateStat(Stat->GetBaseStat(), Stat->GetModifierStat());
		HpBarWidget->UpdateHpBar(Stat->GetCurrentHp());
		Stat->OnHpChanged.AddUObject(HpBarWidget, &UMHHpBarWidget::UpdateHpBar);
		Stat->OnStatChanged.AddUObject(HpBarWidget, &UMHHpBarWidget::UpdateStat);
	}
}


void AMHCharacterBase::TakeItem(UMHItemData* InItemData)
{
	if (InItemData)
	{
		TakeItemActions[(uint8)InItemData->Type].ItemDelegate.ExecuteIfBound(InItemData);
	}
}

void AMHCharacterBase::EquipWeapon(UMHItemData* InItemData)
{
	UE_LOG(LogMHCharacter, Log, TEXT("Have Weapon"));

	UMHWeaponItemData* WeaponItemData = Cast<UMHWeaponItemData>(InItemData);

	if (WeaponItemData)
	{
		if (WeaponItemData->WeaponMesh.IsPending())
		{
			WeaponItemData->WeaponMesh.LoadSynchronous();
		}
		Weapon->SetSkeletalMesh(WeaponItemData->WeaponMesh.Get());
	}

}

void AMHCharacterBase::DrinkPotion(UMHItemData* InItemData)
{
	UE_LOG(LogMHCharacter, Log, TEXT("Drink Potion"));

	UMHPotionItemData* PotionItemData = Cast<UMHPotionItemData>(InItemData);
	if (PotionItemData)
	{
		Stat->HealHp(PotionItemData->HealAmount);
	}

}

void AMHCharacterBase::ReadScroll(UMHItemData* InItemData)
{
	UE_LOG(LogMHCharacter, Log, TEXT("Read Scroll"));
}

void AMHCharacterBase::ApplyStat(const FMHCharacterStat& BaseStat, const FMHCharacterStat& ModifierStat)
{
	float MovementSpeed = (BaseStat + ModifierStat).MovementSpeed;
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}



