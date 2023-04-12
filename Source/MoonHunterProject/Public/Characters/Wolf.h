// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Wolf.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MOONHUNTERPROJECT_API AWolf : public ACharacter
{
	GENERATED_BODY()

public:
	
	AWolf();

protected:
	
	virtual void BeginPlay() override;

private:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	//void SwitchCharacter();

public :

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* Camera;

	/*UPROPERTY(EditAnywhere, Category = "Possession")
	AWolf* OtherCharacter;*/

};
