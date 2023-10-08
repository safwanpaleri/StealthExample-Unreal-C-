// Fill out your copyright notice in the Description page of Project Settings.


#include "YinTriggerBox.h"

void AYinTriggerBox::BeginPlay()
{
	Super::BeginPlay();
}

//Setting up the Trigger box
AYinTriggerBox::AYinTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AYinTriggerBox::YinTrigger);
}

//Functionality when operlapping occurs
void AYinTriggerBox::YinTrigger(AActor* overlappedActor, AActor* otherActor)
{
	//Checking if the overlapped character is Yin and if it is yin then play pickup montage from yin script
	if (otherActor && otherActor != this)
	{
		ACharacter_Yin* yin = Cast<ACharacter_Yin>(otherActor);
		if (yin )
		{
			yin->PlayPickUpMontage();
		}
	}
}
