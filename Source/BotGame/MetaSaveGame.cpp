// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "MetaSaveGame.h"



UMetaSaveGame::UMetaSaveGame()
{

}

void UMetaSaveGame::FillSaveGame(FPlayerMetaStruct PlayerMeta)
{
	this->PlayerMeta = PlayerMeta;
}