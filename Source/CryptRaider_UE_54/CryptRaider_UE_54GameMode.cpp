// Copyright Epic Games, Inc. All Rights Reserved.

#include "CryptRaider_UE_54GameMode.h"
#include "CryptRaider_UE_54Character.h"
#include "UObject/ConstructorHelpers.h"

ACryptRaider_UE_54GameMode::ACryptRaider_UE_54GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
