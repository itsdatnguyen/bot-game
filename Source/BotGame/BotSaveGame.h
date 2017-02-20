// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "BotGameInstance.h"
#include "BotSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BOTGAME_API UBotSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	FPlayerStatStruct PlayerStats;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	TArray<FBotInstance> BotInstanceArray;

public:
	UBotSaveGame();

	void FillSaveGame(FPlayerStatStruct PlayerStats, TArray<FBotInstance> BotInstanceArray);
	/*
	UFUNCTION(BlueprintCallable, Category = "Save")
	FString GetPlayerName() const { return PlayerName; }
	UFUNCTION(BlueprintCallable, Category = "Save")
	void SetPlayerName(FString val) { PlayerName = val; }

	UFUNCTION(BlueprintCallable, Category = "Save")
	FString GetSaveSlotName() const { return SaveSlotName; }
	UFUNCTION(BlueprintCallable, Category = "Save")
	void SetSaveSlotName(FString val) { SaveSlotName = val; }
	*/
};
