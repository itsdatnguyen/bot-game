// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "SaveGameManager.h"
#include "BotGameInstance.h"
#include "BotSaveGame.h"
#include "MetaSaveGame.h"
#include "Bot.h"

#include "BotGameModeBase.h"

/*
Slot names for save games are just 0, 1, 2, 3 etc...
Slot names for meta save files are 0_meta, 1_meta, 3_meta etc...
Max amount of saves are 32.
*/

// Sets default values
ASaveGameManager::ASaveGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MetaSuffix = FString("_meta");
}

// Called when the game starts or when spawned
void ASaveGameManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASaveGameManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
}

void ASaveGameManager::SaveGame(FString SaveName)
{
	UBotSaveGame* SaveGame = Cast<UBotSaveGame>(UGameplayStatics::CreateSaveGameObject(SaveGameClass));
	UMetaSaveGame* MetaSaveGame = Cast<UMetaSaveGame>(UGameplayStatics::CreateSaveGameObject(SaveMetaClass));
	UBotGameInstance* GameInstance = Cast<UBotGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (SaveGame && GameInstance && MetaSaveGame) {
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABot::StaticClass(), Actors);

		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("wtf %d"), Actors.Num()));

		GameInstance->UpdateBotInstances(Actors, true);

		SaveGame->FillSaveGame(GameInstance->PlayerStats, GameInstance->BotInstanceArray);

		GameInstance->PlayerMeta.DoesExist = false;
		MetaSaveGame->FillSaveGame(GameInstance->PlayerMeta);

		if (ValidateSaveGame(SaveGame, MetaSaveGame)) {
			UGameplayStatics::SaveGameToSlot(SaveGame, SaveName, 0);
			UGameplayStatics::SaveGameToSlot(MetaSaveGame, SaveName.Append(MetaSuffix), 0);
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("ERROR! SAVE GAME IS NOT VALID."));
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("ERROR! COULD NOT SAVE."));
	}
}

void ASaveGameManager::LoadGame(FString SaveName)
{
	UBotSaveGame* SaveGame = Cast<UBotSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveName, 0));
	UMetaSaveGame* MetaSaveGame = Cast<UMetaSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveName.Append(MetaSuffix), 0));
	UBotGameInstance* GameInstance = Cast<UBotGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (SaveGame && MetaSaveGame && GameInstance) {
		GameInstance->PlayerStats = SaveGame->PlayerStats;
		GameInstance->BotInstanceArray = SaveGame->BotInstanceArray;
		GameInstance->PlayerMeta = MetaSaveGame->PlayerMeta;

		Cast<ABotGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->SpawnGameInstanceTest(GameInstance->PlayerMeta, GameInstance->PlayerStats, GameInstance->BotInstanceArray);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("ERROR! COULD NOT LOAD"));
	}
}

bool ASaveGameManager::ValidateSaveGame(UBotSaveGame* SaveGame, UMetaSaveGame* MetaSaveGame)
{
	return true;
}

TArray<FPlayerMetaStruct> ASaveGameManager::LoadAllMetaData()
{
	TArray<FPlayerMetaStruct> MetaArray;
	MetaArray.AddDefaulted(MaxSaves);
	for (int i = 0; i < MaxSaves; i++) {
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("Yes this is here."));
		MetaArray[i].DoesExist = false;
		FString SlotString(i + "_meta");
		if (UGameplayStatics::DoesSaveGameExist(SlotString, 0)) {
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString(SlotString + " Is Valid"));
			UMetaSaveGame* SaveGame = Cast<UMetaSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotString, 0));
			SaveGame->PlayerMeta.DoesExist = true;
			MetaArray[i] = SaveGame->PlayerMeta;
		}
	}
	return MetaArray;
}


bool ASaveGameManager::IsSaveSlotValid(FString SaveName)
{
	return (UGameplayStatics::DoesSaveGameExist(SaveName, 0) && UGameplayStatics::DoesSaveGameExist(SaveName.Append(MetaSuffix), 0));
}