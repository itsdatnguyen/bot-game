// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Bot.h"
#include "ChassisComponent.h"
#include "BotEditManager.generated.h"

UCLASS()
class BOTGAME_API ABotEditManager : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TSubclassOf<ABotEditPlatform> PlatformClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TSubclassOf<ABotComponentInventory> InventoryClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TSubclassOf<UBotEditWidget> WidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TSubclassOf<AEquipment> DefaultEquipmentClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TSubclassOf<ABot> BotSpawnClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bot")
	class ABot* CurrentBot;

private:
	ABotEditPlatform* BotEditPlatform;

	ABotComponentInventory* BotComponentInventory;

	UBotEditWidget* BotEditWidget;

public:	
	// Sets default values for this actor's properties
	ABotEditManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	UFUNCTION(BlueprintCallable, Category = "Manager")
	ABotEditPlatform* GetBotEditPlatform() const { return BotEditPlatform; }

	UFUNCTION(BlueprintCallable, Category = "Manager")
	ABotComponentInventory* GetBotComponentInventory() const { return BotComponentInventory; }

	UFUNCTION(BlueprintCallable, Category = "Manager")
	UBotEditWidget* GetBotEditWidget() const { return BotEditWidget; }

	UFUNCTION(BlueprintCallable, Category = "Manager")
	void SpawnNewEquipment(int Rows, int Columns, ABot* Bot);

	UFUNCTION(BlueprintCallable, Category = "Manager")
	TArray<ABot*> ReloadLevel();

private:
	void SpawnHelpers();
};
