// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WolfAnimInstance.h"
#include "Characters/Wolf.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UWolfAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Wolf = Cast<AWolf>(TryGetPawnOwner());
	/*if (Wolf)
	{
		WolfMovement = Wolf->GetCharacterMovement();
	}*/
}

void UWolfAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	/*if (WolfMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(WolfMovement->Velocity);
		IsFalling = WolfMovement->IsFalling();
	}*/

	/*auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		FVector Velocity = Pawn->GetVelocity();
		Velocity.Z = 0;
		GroundSpeed = Velocity.Size();
		Direction = (UE_AnimInstance->CalculateDirection(Velocity, Wolf->GetActorRotation()));
	}*/

	if (Wolf == nullptr)
	{
		Wolf = Cast<AWolf>(TryGetPawnOwner());
	}
	//AWolf *Wolf = Cast<AWolf>(TryGetPawnOwner());

	if (Wolf)
	{
		FVector Velocity = Wolf->GetVelocity(); //속도
		Velocity.Z = 0;
		GroundSpeed = Velocity.Size(); //속력, normalize하면 방향만
		Direction = CalculateDirection(Velocity, Wolf->GetActorRotation());
		IsInAir = Wolf->GetMovementComponent()->IsFalling();
	}
}


