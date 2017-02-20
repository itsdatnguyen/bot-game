// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "GameInstanceTest.h"


// Sets default values
AGameInstanceTest::AGameInstanceTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameInstanceTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameInstanceTest::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

