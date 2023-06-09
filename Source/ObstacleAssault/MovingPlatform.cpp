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

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	
	if (ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MovedDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	// UE_LOG(LogTemp, Display, TEXT("%s Rotating..."), *GetName());
	FRotator CurrentRotation = GetActorRotation();
	// -90도에서 +90도로 돌아갈때 에러처리가 쉽지 않음.
	// CurrentRotation = CurrentRotation + RotationVelocity * DeltaTime;
	// SetActorRotation(CurrentRotation);
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MovedDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}