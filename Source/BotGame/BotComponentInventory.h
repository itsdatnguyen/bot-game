// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Hull.h"
#include "Movement.h"
#include "Power.h"
#include "Weapon.h"
#include "BotComponentInventory.generated.h"

UCLASS()
class BOTGAME_API ABotComponentInventory : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TArray<TSubclassOf<AHull>> HullComponents;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TArray<TSubclassOf<AMovement>> MovementComponents;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TArray<TSubclassOf<APower>> PowerComponents;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TArray<TSubclassOf<AWeapon>> WeaponComponents;

public:	
	// Sets default values for this actor's properties
	ABotComponentInventory();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void FindComponents();
	
};
