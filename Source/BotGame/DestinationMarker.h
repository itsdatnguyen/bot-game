// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DestinationMarker.generated.h"

UCLASS()
class BOTGAME_API ADestinationMarker : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Static Mesh")
	class UStaticMeshComponent* StaticMesh;
	
public:	
	// Sets default values for this actor's properties
	ADestinationMarker();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
