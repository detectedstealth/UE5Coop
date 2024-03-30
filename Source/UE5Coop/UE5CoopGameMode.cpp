// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5CoopGameMode.h"
#include "UE5CoopCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE5CoopGameMode::AUE5CoopGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AUE5CoopGameMode::HostLANGame()
{
	GetWorld()->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

void AUE5CoopGameMode::JoinLANGame()
{
	APlayerController* PC = GetGameInstance()->GetFirstLocalPlayerController();
	if (PC)
	{
		// TODO: Add IP 
		PC->ClientTravel("", TRAVEL_Absolute);
	}
}
