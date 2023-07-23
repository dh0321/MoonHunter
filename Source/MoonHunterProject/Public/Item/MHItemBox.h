// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MHItemBox.generated.h"

UCLASS()
class MOONHUNTERPROJECT_API AMHItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	AMHItemBox();


protected:

	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class UBoxComponent> Trigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	TObjectPtr<class UNiagaraComponent> Effect;

	UPROPERTY(EditAnywhere, Category = Item)
	TObjectPtr<class UMHItemData> Item;


	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/*UFUNCTION()
	void OnEffectFinished(class UNiagaraComponent* NiagaraComponent);*/

};
