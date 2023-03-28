// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Wolf.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


AWolf::AWolf()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 500.f;
	//SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);

}


void AWolf::BeginPlay()
{
	Super::BeginPlay();
	
}


void AWolf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWolf::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AWolf::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AWolf::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &AWolf::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &AWolf::LookUp);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &AWolf::Jump);

}

void AWolf::MoveForward(float Value)
{
	if (Controller && (Value != 0.f))
	{
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AWolf::MoveRight(float Value)
{
	if (Controller && (Value != 0.f))
	{
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AWolf::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AWolf::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

