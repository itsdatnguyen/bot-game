// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "BotGameInstance.generated.h"

class ASaveGameManager;
/**
 * 
 */
UCLASS()
class BOTGAME_API UBotGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "GameInstance")
	FPlayerStatStruct PlayerStats;

	UPROPERTY(BlueprintReadWrite, Category = "GameInstance")
	TArray<FBotInstance> BotInstanceArray;

	UPROPERTY(BlueprintReadWrite, Category = "GameInstance")
	FPlayerMetaStruct PlayerMeta;

private:
	TArray<int> SelectedBotIndices;

public:
	UFUNCTION(BlueprintCallable, Category = "GameInstance")
	void UpdateBotInstance(TArray<ABot*> BotsToUpdate, bool OverwriteExisting);

	UFUNCTION(BlueprintCallable, Category = "GameInstance")
	void UpdateBotInstances(TArray<AActor*> BotsToUpdate, bool OverwriteExisting);

	// Selected Bot Indices functions
	UFUNCTION(BlueprintCallable, Category = "GameInstance")
	void ClearSelectedBotIndices() { SelectedBotIndices.Empty(); }

	UFUNCTION(BlueprintCallable, Category = "GameInstance")
	void AddSelectedBotIndices(int Index);

	UFUNCTION(BlueprintCallable, Category = "GameInstance")
	TArray<int> GetSelectedBotIndices() const { return SelectedBotIndices; }

private:
	void AddBotInstance(ABot* BotActor);
};
