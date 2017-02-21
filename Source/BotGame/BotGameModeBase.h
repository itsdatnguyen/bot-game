// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "BotGameModeBase.generated.h"

class Bot;
class ChassisComponent;
class BotSpawnMethod;

/**
 * 
 */
UCLASS()
class BOTGAME_API ABotGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TSubclassOf<ASaveGameManager> SaveManagerClass;

private:
	UPROPERTY()
	TArray<ABot*> AllBots;

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Utilities")
	bool Is2DVectorInRectangle(FVector2D Point, FVector2D RectStart, FVector2D RectEnd);

	UFUNCTION(BlueprintCallable, Category = "Utilities")
	ASaveGameManager* GetSaveGameManager();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	ABot* SpawnBot(TSubclassOf<ABot> BotClass, FString BotName, FChassisStatStruct ChassisStats, FVector Location, FRotator Rotation, ESpawnActorCollisionHandlingMethod SpawnMethod);

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	AEquipment* SpawnEquipment(TSubclassOf<AEquipment> EquipmentClass, FVector Location, FRotator Rotation, ESpawnActorCollisionHandlingMethod SpawnMethod);

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	ABot* SpawnBotFromInstance(FBotInstance BotInstance, FVector Location, FRotator Rotation, EEquipmentSpawnMethod EquipmentSpawnMethod, ESpawnActorCollisionHandlingMethod SpawnMethod);

	//UFUNCTION(BlueprintCallable, Category = "Spawn")
	//UBotPhysicsConstraintComponent* CreatePhysicsConstraintComponent(AActor * RootActor, AActor * AttachedActor, FName ConstraintName);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	TArray<ABot*> GetAllBots() const { return AllBots; }

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void AddBot(ABot* BotToAdd);

	void SpawnGameInstanceTest(FPlayerMetaStruct PlayerMeta, FPlayerStatStruct PlayerStats, TArray<FBotInstance> BotInstanceArray);

private:
	AEquipment* SpawnEquipmentForInstance(ABot * Bot, TSubclassOf<AEquipment> EquipmentClass, FRotator Rotation, FVector RelativeLocation);
};
