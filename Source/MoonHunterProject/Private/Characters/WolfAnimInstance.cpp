// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WolfAnimInstance.h"
#include "Characters/Wolf.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


UWolfAnimInstance::UWolfAnimInstance()
{
	MovingThreshould = 3.0f;
	JumpingThreshould = 100.f;
}

void UWolfAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
	
}

void UWolfAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		Direction = CalculateDirection(Velocity, Owner->GetActorRotation());
		bIsIdle = GroundSpeed < MovingThreshould;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);
	}
}


