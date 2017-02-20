// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GameInstanceTest.generated.h"

UCLASS()
class BOTGAME_API AGameInstanceTest : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameInstance")
	FPlayerMetaStruct PlayerMeta;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameInstance")
	FPlayerStatStruct PlayerStats;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameInstance")
	TArray<FBotInstance> BotInstanceArray;

public:	
	// Sets default values for this actor's properties
	AGameInstanceTest();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
