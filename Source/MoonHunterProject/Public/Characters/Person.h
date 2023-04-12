// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Person.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MOONHUNTERPROJECT_API APerson : public ACharacter
{
	GENERATED_BODY()

public:
	
	APerson();

protected:
	
	virtual void BeginPlay() override;


private:	
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

public :

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	

};
