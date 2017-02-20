// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "BotComponentInventory.h"

// Sets default values
ABotComponentInventory::ABotComponentInventory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABotComponentInventory::BeginPlay()
{
	Super::BeginPlay();
	//FindComponents();
}

// Called every frame
void ABotComponentInventory::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ABotComponentInventory::FindComponents()
{
	for (TObjectIterator<UClass> It; It; ++It) {
		if (It->IsChildOf(AHull::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract)) {
			HullComponents.Add(It->StaticClass());
		}	
	}
}