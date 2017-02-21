// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameTickable.generated.h"

/** Actors that implement IGameTickable will tick 10 times per second when in battle. (per 1/10 seconds)
 * 
 */
UINTERFACE(BlueprintType)
class BOTGAME_API UGameTickable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class BOTGAME_API IGameTickable
{
	GENERATED_IINTERFACE_BODY()

public:
	// Must implement function 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
	void GameTick(float DeltaSeconds);
};