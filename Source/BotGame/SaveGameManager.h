// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SaveGameManager.generated.h"

class UBotSaveGame;
class UMetaSaveGame;
class UBotStruct;

UCLASS()
class BOTGAME_API ASaveGameManager : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TSubclassOf<USaveGame> SaveGameClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TSubclassOf<UMetaSaveGame> SaveMetaClass;

	static constexpr int MaxSaves = 32;

	FString MetaSuffix;
	
public:	
	// Sets default values for this actor's properties
	ASaveGameManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "Manager")
	void SaveGame(FString SaveName);

	UFUNCTION(BlueprintCallable, Category = "Manager")
	void LoadGame(FString SaveName);

	UFUNCTION(BlueprintCallable, Category = "Manager")
	TArray<FPlayerMetaStruct> LoadAllMetaData();

	UFUNCTION(BlueprintCallable, Category = "Manager")
	bool IsSaveSlotValid(FString SaveName);

private:
	bool ValidateSaveGame(UBotSaveGame* SaveGame, UMetaSaveGame* MetaSaveGame);
};
