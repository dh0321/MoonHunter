// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WolfAnimInstance.h"
#include "Characters/Wolf.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UWolfAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Wolf = Cast<AWolf>(TryGetPawnOwner());
	if (Wolf)
	{
		WolfMovement = Wolf->GetCharacterMovement();
	}
}

void UWolfAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (WolfMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(WolfMovement->Velocity);
		IsFalling = WolfMovement->IsFalling();
	}
}


