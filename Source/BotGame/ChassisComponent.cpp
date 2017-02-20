// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "ChassisComponent.h"


// Sets default values for this component's properties
UChassisComponent::UChassisComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UChassisComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UChassisComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

