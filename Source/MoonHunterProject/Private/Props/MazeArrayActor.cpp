// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/MazeArrayActor.h"

AMazeArrayActor::AMazeArrayActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMazeArrayActor::BeginPlay()
{
	Super::BeginPlay();

	SizeX = 20;
	SizeY = 20;

	MazeArray.Init(TArray<bool>(), SizeX);

	for (int32 i = 0; i < SizeX; i++)
	{
		MazeArray[i].Init(false, SizeY);
	}

	for (int32 i = 0; i < SizeX; i++)
	{
		bool bIsXOdd = i % 2 == 1; //true È¦¼ö
		if (bIsXOdd == true)
		{
			for (int32 j = 0; j < SizeY; j++)
			{
				/*bool bisyodd = j % 2 == 1;
				if (bisyodd == true)
					Mazearray[i][j] = true;*/

					/*if (j % 2 == 1)
						MazeArray[i][j] = true;*/

				MazeArray[i][j] = j % 2 == 1;
			}
		}
	}


	for (int32 i = 0; i < SizeX / 2; i++)
	{
		for (int32 j = 0; j < SizeY / 2; j++)
		{
			if (MazeArray[i * 2 + 1][j * 2 + 1])
			{
				int32 RandNum = GetRandomPosition();

				switch (RandNum)
				{
				case 1: //¿ÞÂÊ
					MazeArray[2 * i][2 * j + 1] = true;
					break;

				case 2: //¾Æ·¡ÂÊ
					MazeArray[2 * i + 1][2 * j] = true;
					break;
				}
			}
		}
	}

	FVector Offset = Cube->GetActorLocation();

	for (int32 i = 0; i < SizeX; i++)
	{
		for (int32 j = 0; j < SizeY; j++)
		{
			if (MazeArray[i][j] == false)
			{
				FVector CubeLocation = FVector(i * 400.f, j * 400.f, 200.f);

				UWorld* World = Cube->GetWorld();
				FActorSpawnParameters SpawnParams;
				SpawnParams.Template = Cube;
				World->SpawnActor<AActor>(Cube->GetClass(), CubeLocation - Offset, FRotator(0.f, 0.f, 0.f), SpawnParams);
			}
		}
	}
}

void AMazeArrayActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 AMazeArrayActor::GetRandomPosition()
{
	return FMath::RandRange(1, 2);
}
