// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeArrayActor.generated.h"

UCLASS()
class MOONHUNTERPROJECT_API AMazeArrayActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMazeArrayActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	int32 SizeX;

	UPROPERTY(EditAnywhere)
	int32 SizeY;

	TArray<TArray<bool>> MazeArray;

	UFUNCTION()
	int32 GetRandomPosition();

	UPROPERTY(EditAnywhere)
	AActor* Cube;

};
