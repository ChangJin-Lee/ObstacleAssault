// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();

	FString Name = GetName();
	// FString MyString = "My String Value";

	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
	// UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: %s"), *MyString);
	// UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: %f"), MovedDistance);
	// UE_LOG(LogTemp, Warning, TEXT("Your message"));
	// UE_LOG(LogTemp, Error, TEXT("Your message"));
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move platform forwards
		// Get current location
	FVector CurrentLocation = GetActorLocation();
		// Add vector to that location
	CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;
		// Set the location
	SetActorLocation(CurrentLocation);
	// Send platform back if gone too far
		// Check how far we've moved
	float DistancedMoved =  FVector::Dist(StartLocation, CurrentLocation);
		// Reverse direction of motion if gone too far
	if (DistancedMoved > MovedDistance)
	{
		float OverShoot = DistancedMoved - MovedDistance;
		FString Name = GetName();
		UE_LOG(LogTemp, Display, TEXT("%s Platform overshot by %f"), *Name, OverShoot);
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MovedDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
		

}

