// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// FRotator MyRotation = GetComponentRotation();
	// FString RotationString = MyRotation.ToCompactString();
	// UE_LOG(LogTemp, Display, TEXT("Grabber Rotation: %s"), *RotationString);

	// float Time = GetWorld()->TimeSeconds;
	// UE_LOG(LogTemp, Display, TEXT("Time Seconds: %f"), Time);

	

	// float Damage = 5;
	// float& DamageRef = Damage;
	// DamageRef = 5;
	// UE_LOG(LogTemp, Display, TEXT("DamageRef Value: %f, Damage Value: %f"), DamageRef, Damage);

	// PrintDamageValue(Damage);
	// UE_LOG(LogTemp, Display, TEXT("Damage Value after function call: %f"), Damage);

	
	// else
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("No Actor Hit"));
	// }

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	// if(PhysicsHandle == nullptr)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("No Physics Handle Component Found"));
	// 	return;
	// }

	if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
	PhysicsHandle->SetTargetLocationAndRotation(
		TargetLocation,
		GetComponentRotation()
	);
	}

	
}

// void UGrabber::PrintDamageValue(const float& DamageValue)
// {
// 	// DamageValue = 10;
// 	UE_LOG(LogTemp, Display, TEXT("Damage Value inside function: %f"), DamageValue);
// }



void UGrabber::Grab()
{
	// UE_LOG(LogTemp, Display, TEXT("Grabber Grab"));
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	// if(PhysicsHandle == nullptr)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("No Physics Handle Component Found"));
	// 	return;
	// }

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);
	if (HasHit)
	{
		// DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Yellow, false, 5);
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Green, false, 5);
		// AActor* HitActor = HitResult.GetActor();
		// if (HitActor)
		// {
		// 	FString ActorName = HitActor->GetActorNameOrLabel();
		// 	UE_LOG(LogTemp, Display, TEXT("Hit Actor: %s"), *ActorName);
		// }

		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->SetSimulatePhysics(true);
		HitComponent->WakeAllRigidBodies();
		AActor* HitActor = HitComponent->GetOwner();
		HitActor->Tags.Add("Grabbed");
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}

void UGrabber::Release()
{
	// UE_LOG(LogTemp, Display, TEXT("Grabber Release"));
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	// if(PhysicsHandle)
	// {
	// 	return;
	// }

	if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
	}
	
}


// Comman code to get Physics Handle Component
UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const{
	UPhysicsHandleComponent* Result =  GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(Result)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent"));
	}
	return Result;
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const{
	FVector Start = GetComponentLocation();
	FVector End = Start + (GetForwardVector() * MaxGrabDistance);
	// DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	// DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);

	return GetWorld()->SweepSingleByChannel(
		/* OutHit */	OutHitResult,
		/* Start */		Start,
		/* End */		End,
		/* Rot */		FQuat::Identity,
		/* Channel */	ECC_GameTraceChannel2,
		/* Shape */		FCollisionShape::MakeSphere(GrabRadius)
	);
}