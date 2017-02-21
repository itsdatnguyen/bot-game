// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GameTickManager.generated.h"

class IGameTickable;

UCLASS()
class BOTGAME_API AGameTickManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameTickManager();

private:
	UPROPERTY()
	FTimerHandle TickHandle;

	// The time for the timer to repeat itself
	UPROPERTY()
	float TimerDelay = 0.1f;

	// Array of objects that will be ticked
	TArray<IGameTickable*> TickableObjects;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GameTick();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Tick")
	void SetTimerDelay(float Delay) {if(Delay > 0.f) {TimerDelay = Delay;} }

	UFUNCTION(BlueprintCallable, Category = "Tick")
	float GetTimerDelay() const {return TimerDelay;}

	UFUNCTION(BlueprintCallable, Category = "Tick")
	void RegisterTickableObject(IGameTickable* Object);
	
	UFUNCTION(BlueprintCallable, Category = "Tick")
	void RemoveTickableObject(IGameTickable* Object);
};
