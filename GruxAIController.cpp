// Fill out your copyright notice in the Description page of Project Settings.


#include "GruxAIController.h"
#include "Kismet/GameplayStatics.h"

void AGruxAIController::BeginPlay()
{
	Super::BeginPlay();

	//Setting up initial reference values
	playerCharacter = Cast<ACharacter_Yin>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	thisCharacter = Cast<ACharacter_Grux>(GetPawn());
	myLocation = thisCharacter->GetActorLocation();

	//From the character current location 4 locations are created to move from and to
	Loc1 = FVector(myLocation.X, myLocation.Y + 250.0f, myLocation.Z);
	Loc2 = FVector(myLocation.X, myLocation.Y - 250.0f, myLocation.Z);
	Loc3 = FVector(myLocation.X + 250.0f, myLocation.Y, myLocation.Z);
	Loc4 = FVector(myLocation.X - 250.0f, myLocation.Y, myLocation.Z);
	
	//An interval between movements.
	NextMovementTime = FMath::FRandRange(MovementIntervalMin, MovementIntervalMax);
	bHasNoticed = false;
}

void AGruxAIController::Tick(float DeltaTime)
{
	Super::Tick((DeltaTime));

	//if the character is dead, then return immedietly 
	if (thisCharacter->bIsDead)
		return;

	//Checking if the player is infront of this character
	//if yes then call this character's AlertRoar function
	if (CheckIfInfrontOfActor())
	{
		thisCharacter->AlertRoar();
	}
	
	//After certain random time between 5-10 seconds and the player is not infront of us, 
	//then select random location from 4 location we created at the BeginPlay and move towards it.
	if (GetWorld()->GetTimeSeconds() >= NextMovementTime && !bHasNoticed)
	{
		// Choose a random location
		FVector RandomLocation;
		int32 RandomIndex = FMath::RandRange(1, 4);
		switch (RandomIndex)
		{
		case 1:
			RandomLocation = Loc1;
			break;
		case 2:
			RandomLocation = Loc2;
			break;
		case 3:
			RandomLocation = Loc3;
			break;
		case 4:
			RandomLocation = Loc4;
			break;
		default:
			RandomLocation = Loc1; // Default to Loc1
			break;
		}

		//Move to Location
		FVector CurrentLocation = GetPawn()->GetActorLocation(); // Current location of the character
		FRotator NewRotation = (RandomLocation - CurrentLocation).Rotation();
		FRotator CurrentRotation = GetPawn()->GetActorRotation();
		FRotator SmoothedRotation = FMath::RInterpTo(CurrentRotation, NewRotation, DeltaTime, 10.0f);
		GetPawn()->SetActorRotation(SmoothedRotation);
		MoveToLocation(RandomLocation);

		//select a random time to move again.
		NextMovementTime = GetWorld()->GetTimeSeconds() + FMath::FRandRange(MovementIntervalMin, MovementIntervalMax);
	}
	
}

//Function to check whether the player is infront of us.
bool AGruxAIController::CheckIfInfrontOfActor()
{
	//Gets this characters current location and player's current location
	//takes the dot product and see if the player is infront of this character
	//if yes, then we check whether the player is hiding behind a wall or obstacle using raycast,
	// if the player is not hiding and is infront of us then returns true
	// else returns false.
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter)
	{
		FVector StartLocation = thisCharacter->GetActorLocation();
		FVector EndLocation = playerCharacter->GetActorLocation();

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		ActorToPlayer = EndLocation - StartLocation;
		ActorToPlayer.Normalize();

		DotProduct = FVector::DotProduct(thisCharacter->GetActorForwardVector(), ActorToPlayer);

		if (DotProduct > 0.6f)
		{
			if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams))
			{
				AActor* HitActor = HitResult.GetActor();
				ACharacter_Yin* YinHit = Cast<ACharacter_Yin>(HitActor);
				if (YinHit)
				{
					bHasNoticed = true;
					return true;
				}

				if (HitActor == PlayerCharacter)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Raycast Hit 2"));
					bHasNoticed = true;
					return true;
				}

			}
		}

	}
	else
	{
		bHasNoticed = false;
		return false;
		
	}
	bHasNoticed = false;
	return false;
}
