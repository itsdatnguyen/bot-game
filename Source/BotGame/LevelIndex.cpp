// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "LevelIndex.h"


// Sets default values
ALevelIndex::ALevelIndex()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ALevelIndex::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALevelIndex::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
