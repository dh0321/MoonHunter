// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/MHItemBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Physics/MHCollision.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Interface/MHCharacterItemInterface.h"


AMHItemBox::AMHItemBox()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	Trigger->SetCollisionProfileName(CPROFILE_MHTRIGGER);
	Trigger->SetGenerateOverlapEvents(true);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMHItemBox::OnOverlapBegin);

	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	Effect->bAutoActivate = false;

}



void AMHItemBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (nullptr == Item)
	{
		Destroy();
		return;
	}

	IMHCharacterItemInterface* OverlappingPawn = Cast<IMHCharacterItemInterface>(OtherActor);
	if (OverlappingPawn)
	{
		OverlappingPawn->TakeItem(Item);
	}

	Effect->Activate(true);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	//Effect->OnSystemFinished.AddDynamic(this, &AMHItemPotion::OnEffectFinished);
}

//void AMHItemPotion::OnEffectFinished(UNiagaraComponent* NiagaraComponent)
//{
//
//}


