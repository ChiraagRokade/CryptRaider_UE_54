// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponentC.h"

void UTriggerComponentC::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
    UE_LOG(LogTemp, Display, TEXT("test"));
}