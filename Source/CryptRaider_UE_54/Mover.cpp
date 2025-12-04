// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

#include "Math/UnrealMathUtility.h"
// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	OriginalLocation = GetOwner()->GetActorLocation();
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	// AActor* Owner = GetOwner();

	// // float MyFloat = 5;
	// // float* YourFloat = &MyFloat;
	// // UE_LOG(LogTemp, Display, TEXT("YourFloat Value: %f"), *YourFloat);

	// FString Name = Owner->GetActorNameOrLabel();

	// UE_LOG(LogTemp, Display, TEXT("Mover Owner Address: %s"), *Name);

	// FVector CharacterLocation = Owner->GetActorLocation();
	// FString ChaLocString = CharacterLocation.ToCompactString();
	// UE_LOG(LogTemp, Display, TEXT("Character address: %s"), *ChaLocString);

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector TargetLocation = OriginalLocation + MoveOffset;
	float Speed = FVector::Distance(OriginalLocation, TargetLocation) / MoveTime;

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	
	if(ShouldMove == true)
		GetOwner()->SetActorLocation(NewLocation);
}

