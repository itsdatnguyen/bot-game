// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LevelIndex.generated.h"

UCLASS()
class BOTGAME_API ALevelIndex : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level")
	TArray<FString> Levels;

public:	
	// Sets default values for this actor's properties
	ALevelIndex();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
