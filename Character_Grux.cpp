// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Grux.h"

// Sets default values
ACharacter_Grux::ACharacter_Grux()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GruxMesh = GetMesh();

}

// Called when the game starts or when spawned
void ACharacter_Grux::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = GetMesh()->GetAnimInstance();
}

void ACharacter_Grux::CollisionFunction(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{

}

// Called every frame
void ACharacter_Grux::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacter_Grux::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//Called when the player kill stealthly
void ACharacter_Grux::StealthKill()
{
	UE_LOG(LogTemp, Warning, TEXT("Stealth Killed Grux"));
	
	//Play animation of death, and after certain seconds destroy the character
	//AnimInstance->StopSlotAnimation();
	PlayAnimMontage(DeathMontage);
	bIsDead = true;
	float WaitTime = 1.3f;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			Destroy();
		}, WaitTime, false);
}

//Function to play roar animation montage.
void ACharacter_Grux::AlertRoar()
{
	if (!AnimInstance->Montage_IsPlaying(RoarMontage))
	{
		PlayAnimMontage(RoarMontage);
		//UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}



