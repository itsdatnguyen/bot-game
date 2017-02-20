// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "BotSaveGame.h"




UBotSaveGame::UBotSaveGame()
{

}

void UBotSaveGame::FillSaveGame(FPlayerStatStruct PlayerStats, TArray<FBotInstance> BotInstanceArray)
{
	this->PlayerStats = PlayerStats;
	this->BotInstanceArray = BotInstanceArray;
}