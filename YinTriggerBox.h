// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFrameWork/Actor.h"
#include  "Character_Yin.h"
#include  "LevelSequence/Public/LevelSequenceActor.h"
#include  "LevelSequence/Public/LevelSequencePlayer.h"
#include "Engine/TriggerBox.h"
#include "YinTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class SAMPEPROJECT_API AYinTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	AYinTriggerBox();

	//Declaring functions
	UFUNCTION()
		void YinTrigger(class AActor* overlappedActor, class AActor* otherActor);

};
