// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponentC.h"

UTriggerComponentC::UTriggerComponentC()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponentC::BeginPlay()
{
	Super::BeginPlay();

	// ...
    // UE_LOG(LogTemp, Display, TEXT("test"));
}

void UTriggerComponentC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
    
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // TArray<AActor*> Actors;
    // GetOverlappingActors(Actors);

    // if(Actors.Num() > 0){
    //     FString ActorName = Actors[0]->GetActorNameOrLabel();
    //     UE_LOG(LogTemp, Display, TEXT("Overlapping Actor: %s"), *ActorName);
    // }

    // int32 i = 0;
    // while(i < Actors.Num()){
    //     FString ActorName = Actors[i]->GetActorNameOrLabel();
    //     UE_LOG(LogTemp, Display, TEXT("Overlapping Actor %d: %s"), i, *ActorName);
    //     ++i;
    // }

    // for(int32 index = 0; index<Actors.Num(); index++){
    //     FString ActorName = Actors[index]->GetActorNameOrLabel();
    //     UE_LOG(LogTemp, Display, TEXT("Overlapping Actor %d: %s"), index, *ActorName);
    // }

    /*******************Range Based for loop*******************/
    // for(AActor* Actor : Actors){
    //     // FString ActorName = Actor->GetActorNameOrLabel();
    //     // UE_LOG(LogTemp, Display, TEXT("Overlapping Actor: %s"), *ActorName);
    //     if(Actor->ActorHasTag(AcceptableTag)){
    //         UE_LOG(LogTemp, Display, TEXT("Unlocking"));
    //     }
    // }
    if(GetAcceptableActor() != nullptr){
        UE_LOG(LogTemp, Display, TEXT("Unlocking"));
    }else{
        UE_LOG(LogTemp, Display, TEXT("Relocking"));
    }
}

AActor* UTriggerComponentC::GetAcceptableActor() const{

    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    for(AActor* Actor : Actors){
        if(Actor->ActorHasTag(AcceptableTag)){
            return Actor;
        }
    }

    return nullptr;
}