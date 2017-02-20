// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Volume.h"
#include "SpawnVolume.generated.h"

/**
 * 
 */
UCLASS()
class BOTGAME_API ASpawnVolume : public AVolume
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	bool IsPlayerSpawnVolume;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	int VolumeId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* StaticMesh;

private:
	UMaterialInstance* PlayerMaterial;

	UMaterialInstance* EnemyMaterial;
	
public:
	ASpawnVolume();

	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;
};
