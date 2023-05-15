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

	UWolfAnimInstance();


protected:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	/*UPROPERTY(BlueprintReadOnly)
	class AWolf* Wolf;

	UPROPERTY(BlueprintReadOnly)
	class UCharacterMovementComponent* WolfMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsInAir;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	FVector Velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float GroundSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsIdle : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float MovingThreshould;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsFalling : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsJumping : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float JumpingThreshould;


private:

};

