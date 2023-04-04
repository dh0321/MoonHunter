// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WolfAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MOONHUNTERPROJECT_API UWolfAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	//UWolfAnimInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	class AWolf* Wolf;

	UPROPERTY(BlueprintReadOnly)
	class UAnimInstance* UE_AnimInstance;

	UPROPERTY(BlueprintReadOnly)
	class UCharacterMovementComponent* WolfMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsFalling;


private:

	
};
