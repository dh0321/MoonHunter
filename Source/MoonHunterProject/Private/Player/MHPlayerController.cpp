// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MHPlayerController.h"

void AMHPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

}
