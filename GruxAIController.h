// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Character_Yin.h"
#include "Kismet/GameplayStatics.h"
#include "GruxAIController.generated.h"

/**
 * 
 */
UCLASS()
class SAMPEPROJECT_API AGruxAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	bool CheckIfInfrontOfActor();

	//References to characters
	UPROPERTY(VisibleAnywhere)
	class ACharacter_Yin* playerCharacter;
	class ACharacter_Grux* thisCharacter;

private:

	//required variables
	FVector myLocation;
	FVector playerLocation;
	FVector ActorToPlayer;
	float DotProduct;

	FVector Loc1;
	FVector Loc2;
	FVector Loc3;
	FVector Loc4;

	float random;
	float NextMovementTime;
	float MovementIntervalMin = 5.0f;
	float MovementIntervalMax = 10.0f;
	bool bHasNoticed = false;
};
