// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PersonAnimInstance.h"
#include "Characters/Person.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UPersonAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Person = Cast<APerson>(TryGetPawnOwner());
	/*if (Person)
	{
		PersonMovement = Person->GetCharacterMovement();
	}*/
}

void UPersonAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	/*if (PersonMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(PersonMovement->Velocity);
		IsFalling = PersonMovement->IsFalling();
	}*/

	if (Person == nullptr)
	{
		Person = Cast<APerson>(TryGetPawnOwner());
	}

	if (Person)
	{
		FVector Velocity = Person->GetVelocity(); //�ӵ�
		Velocity.Z = 0;
		GroundSpeed = Velocity.Size(); //�ӷ�, normalize�ϸ� ���⸸
		Direction = CalculateDirection(Velocity, Person->GetActorRotation());
		IsInAir = Person->GetMovementComponent()->IsFalling();
	}

	
	/*if (PersonMovement)
	{
		IsFalling = PersonMovement->IsFalling();
	}*/


}

