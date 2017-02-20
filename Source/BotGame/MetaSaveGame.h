// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "BotGameInstance.h"
#include "MetaSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BOTGAME_API UMetaSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	FPlayerMetaStruct PlayerMeta;

public:
	UMetaSaveGame();

	void FillSaveGame(FPlayerMetaStruct PlayerMeta);
};
