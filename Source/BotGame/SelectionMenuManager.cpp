// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "SelectionMenuManager.h"
#include "SelectionMenuWidget.h"
#include "LevelIndex.h"

// Sets default values
ASelectionMenuManager::ASelectionMenuManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASelectionMenuManager::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnHelpers();
}

// Called every frame
void ASelectionMenuManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASelectionMenuManager::SpawnHelpers() 
{
	FVector const Location(0, 0, 0);
	FRotator const Rotation(0, 0, 0);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (SelectionMenuClass) {
		SelectionMenuWidget = CreateWidget<USelectionMenuWidget>(GetGameInstance(), SelectionMenuClass);
		SelectionMenuWidget->AddToViewport(0);
	}
	if (LevelIndexClass) {
		LevelIndex = Cast<ALevelIndex>(GetWorld()->SpawnActor(LevelIndexClass, &Location, &Rotation, SpawnParams));
	}
}