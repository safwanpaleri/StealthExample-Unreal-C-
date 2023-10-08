// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Yin.h"

// Sets default values
ACharacter_Yin::ACharacter_Yin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//Setting up this character
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	YinMesh = GetMesh();

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm Component"));
	SpringArm->SetupAttachment(YinMesh);
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetWorldLocation(FVector(0.0f, 0.0f, 180.0f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Character Camera"));
	CameraComponent->SetupAttachment(SpringArm);


}

// Called when the game starts or when spawned
void ACharacter_Yin::BeginPlay()
{
	Super::BeginPlay();
	
	//getting necessary references
	AnimInstance = GetMesh()->GetAnimInstance();

	for (int32 i = 0; i < YinMesh->GetNumChildrenComponents(); i++)
	{
		USceneComponent* ChildComponent = YinMesh->GetChildComponent(i);
		if (ChildComponent->ComponentHasTag("Weapon"))
		{
			WeaponComponent = Cast<UCapsuleComponent>(ChildComponent);
			break;
		}
	}

	if (WeaponComponent != NULL)
	{
		WeaponComponent->OnComponentBeginOverlap.AddDynamic(this, &ACharacter_Yin::CollisionFunction);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponComponent not Found"));
	}
}

// Called every frame
void ACharacter_Yin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacter_Yin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACharacter_Yin::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACharacter_Yin::MoveSideWard);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ACharacter_Yin::LookSide);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ACharacter_Yin::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter_Yin::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ACharacter_Yin::Attack);

}

//Functionaly binded with axis of MoveForward
void ACharacter_Yin::MoveForward(float value)
{
	AddMovementInput(CameraComponent->GetForwardVector(), value);
}

//Functionaly binded with axis of Move Right
void ACharacter_Yin::MoveSideWard(float value)
{
	AddMovementInput(CameraComponent->GetRightVector(), value);
}

//Functionaly binded with axis of LookUp
void ACharacter_Yin::LookUp(float value)
{
	AddControllerPitchInput(value);
}

//Functionaly binded with axis of Turn
void ACharacter_Yin::LookSide(float value)
{
	
	AddControllerYawInput(value);
}

//Functionaly binded with axis of Jump
void ACharacter_Yin::Jump()
{
	Super::Jump();
}

//Functionaly binded with axis of Attack
void ACharacter_Yin::Attack()
{
	//Do Attack
	PlayAnimMontage(MeleeMontage);
}

//Function called whenever PickupMontage to be played
void ACharacter_Yin::PlayPickUpMontage()
{
	UE_LOG(LogTemp, Warning, TEXT("hitted BoxTrigeer 0"));
	PlayAnimMontage(PickUpMontage);
}

//Function responsible collision detection
void ACharacter_Yin::CollisionFunction(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	//if a collision deted and if the collision is happened when we are attacking
	//and if the collision is happened to "Character_Grux" then call the function in the grux character to kill
	if (HitComp != NULL && OtherActor != NULL && OtherComp != NULL)
	{
		if (OtherActor != this && AnimInstance->Montage_IsPlaying(MeleeMontage))
		{
			ACharacter_Grux* script = Cast<ACharacter_Grux>(OtherActor);
			if (script != NULL)
			{
				if(!script->bIsDead)
					script->StealthKill();
			}
			
		}
	}
}


