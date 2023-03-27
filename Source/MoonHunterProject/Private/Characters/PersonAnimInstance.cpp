// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PersonAnimInstance.h"
#include "Characters/Person.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UPersonAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Person = Cast<APerson>(TryGetPawnOwner());
	if (Person)
	{
		PersonMovement = Person->GetCharacterMovement();
	}
}

void UPersonAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	if (PersonMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(PersonMovement->Velocity);
		IsFalling = PersonMovement->IsFalling();
	}
}

