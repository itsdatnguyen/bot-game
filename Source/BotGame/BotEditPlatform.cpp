// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "BotEditPlatform.h"
#include "PlayerCameraController.h"
#include "TileStatics.h"

ABotEditPlatform::ABotEditPlatform()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	PlatformPadding = 4;
}

void ABotEditPlatform::BeginPlay()
{
	Super::BeginPlay();
}

void ABotEditPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABotEditPlatform::ResizePlatform(FInt2DStruct NewScale)
{
	if (StaticMeshComponent) {
		StaticMeshComponent->SetWorldScale3D(FVector(NewScale.Y * (TileStatics::TileSpacingY / 100) + PlatformPadding, NewScale.X * (TileStatics::TileSpacingX / 100) + PlatformPadding, ZScale));
		//SetActorLocation(FVector(NewScale.Y * -50, NewScale.X * -50, 0));
	}
}
