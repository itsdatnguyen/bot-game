// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BattleManager.generated.h"

class ASpawnVolume;

UCLASS()
class BOTGAME_API ABattleManager : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TSubclassOf<UBattleWidget> BattleWidgetClass;

private:
	TArray<ASpawnVolume*> SpawnVolumes;

	UBattleWidget* BattleWidget;
	
public:	
	// Sets default values for this actor's properties
	ABattleManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "Manager")
	UBattleWidget* GetBattleWidget() const {return BattleWidget;}

	UFUNCTION(BlueprintCallable, Category = "Manager")
	void UpdateSpawnVolumes();

private:
	void SpawnBots();
	
};
