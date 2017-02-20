// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "BattleManager.h"
#include "SpawnVolume.h"
#include "BotGameInstance.h"
#include "BotGameModeBase.h"
#include "BattleWidget.h"

// Sets default values
ABattleManager::ABattleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattleManager::BeginPlay()
{
	Super::BeginPlay();
	UpdateSpawnVolumes();
	SpawnBots();

	// Spawn Battle Widget
	if (BattleWidgetClass) {
		BattleWidget = CreateWidget<UBattleWidget>(GetGameInstance(), BattleWidgetClass);
		BattleWidget->AddToViewport(0);
	}
}

// Called every frame
void ABattleManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ABattleManager::UpdateSpawnVolumes()
{
	SpawnVolumes.Empty();

	TArray<AActor*> RetrievedActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), RetrievedActors);

	ASpawnVolume* SpawnVolume;
	for (AActor* Actor : RetrievedActors) {
		SpawnVolume = Cast<ASpawnVolume>(Actor);
		if (SpawnVolume) {
			SpawnVolumes.Add(SpawnVolume);
		}
	}
}

void ABattleManager::SpawnBots()
{
	// Spawn the bots in a arbitary spot so that the bots exist in the map until the player chooses a spot for it
	UBotGameInstance* GameInstance = Cast<UBotGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	ABotGameModeBase* GameMode = Cast<ABotGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	// Spawn properties
	FVector Location(5000, 5000, 5000);
	FRotator Rotation(0, 0, 0);
	EEquipmentSpawnMethod EquipmentSpawnMethod = EEquipmentSpawnMethod::SpawnWithoutDefaultEquipment;
	ESpawnActorCollisionHandlingMethod ActorCollisionMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (GameInstance && GameMode) {
		for (int Index : GameInstance->GetSelectedBotIndices()) {
			if (Index < GameInstance->BotInstanceArray.Num()) {
				GameMode->SpawnBotFromInstance(GameInstance->BotInstanceArray[Index], Location, Rotation, EquipmentSpawnMethod, ActorCollisionMethod);
			}
		}
	}
}