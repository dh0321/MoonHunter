// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PersonAnimInstance.generated.h"


UCLASS()
class MOONHUNTERPROJECT_API UPersonAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	class APerson* Person;

	UPROPERTY(BlueprintReadOnly)
	class UCharacterMovementComponent* PersonMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsInAir;


private:

};
