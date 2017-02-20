// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ChassisComponent.h"
#include "BotEditPlatform.generated.h"

/**
 * 
 */
UCLASS()
class BOTGAME_API ABotEditPlatform : public AActor
{
	GENERATED_BODY()

protected:
	float ZScale = 0.05;

	int PlatformPadding;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "StaticMeshComponent")
	class UStaticMeshComponent* StaticMeshComponent;

public:

	ABotEditPlatform();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Platform")
	void ResizePlatform(FInt2DStruct NewScale);
	
};
