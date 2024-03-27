// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UE5CoopGameMode.generated.h"

UCLASS(minimalapi)
class AUE5CoopGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUE5CoopGameMode();

	UFUNCTION(BlueprintCallable)
	void HostLANGame();

	UFUNCTION(BlueprintCallable)
	void JoinLANGame();
};



