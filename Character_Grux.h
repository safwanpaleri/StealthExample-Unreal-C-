// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Character_Grux.generated.h"

UCLASS()
class SAMPEPROJECT_API ACharacter_Grux : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Grux();

	//Mesh Reference
	UMeshComponent* GruxMesh;

	//CharacterMovement
	UCharacterMovementComponent* GruxCharacterMovement;

	//Animation Montages
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
		UAnimMontage* IdleMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* RoarMontage;

	//Other necessary values
	int health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script_bool")
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script_bool")
	bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* YourPauseWidget;

	bool bHasActivated = false;

	UAnimInstance* AnimInstance;
	FTimerHandle TimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void CollisionFunction(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Function to kill this enemy
	virtual void StealthKill();

	//Function to play alert roar animation montage
	virtual void AlertRoar();
};
