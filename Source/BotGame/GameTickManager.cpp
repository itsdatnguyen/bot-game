// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "GameTickManager.h"


// Sets default values
AGameTickManager::AGameTickManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGameTickManager::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager.SetTimer(TickHandle, AGameTickManager::GameTick, TimerDelay, false, 0.f);
}

// Called every frame
void AGameTickManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameTickManager::GameTick()
{
	for (IGameTickable Tickable : TickableObjects) {
		if (Tickable) {
			Tickable->GameTick(TimerDelay);
		}
		else {
			// this should not be happening, remove object from the game tick
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("Error, Tickable object is not valid"));
		}
	}
	GetWorld()->GetTimerManager.SetTimer(TickHandle, AGameTickManager::GameTick, TimerDelay, false, 0.f);
}

void AGameTickManager::RegisterTickableObject(IGameTickable* Object)
{
	if (Object && !TickableObjects.Contains(Object)) {
		TickableObjects.Add(Object);
	}
}

void AGameTickManager::RemoveTickableObject(IGameTickable* Object)
{
	TickableObjects.RemoveSingle(Object);
}

