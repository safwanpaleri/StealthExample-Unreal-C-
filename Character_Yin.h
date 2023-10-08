#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Runtime/Engine/Classes/GameFramework/SpringArmComponent.h>
#include <Runtime/Engine/Classes/Camera/CameraComponent.h>
#include "Components/CapsuleComponent.h"
#include "Character_Grux.h"
#include "Character_Yin.generated.h"


UCLASS()
class SAMPEPROJECT_API ACharacter_Yin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Yin();

	//Setting up of character
	UMeshComponent* YinMesh;
	UCharacterMovementComponent* YinCharacterMovement;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	UCapsuleComponent* WeaponComponent;


	//Animation Montage references
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* MeleeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* PickUpMontage;

	//Other required variables
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	int health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script_bool")
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script_bool")
	bool bIsAttacking;

	bool bHasActivated = false;

	UAnimInstance* AnimInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Collision function
	UFUNCTION()
    virtual void CollisionFunction(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Input functions
	virtual void MoveForward(float value);
	virtual void MoveSideWard(float value);
	virtual void LookUp(float value);
	virtual void LookSide(float value);
	virtual void Jump();
	virtual void Attack();

	//Function to play pickup montage
	void PlayPickUpMontage();
};
