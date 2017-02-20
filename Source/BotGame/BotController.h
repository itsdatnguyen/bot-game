// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "DestinationMarker.h"
#include "Queue.h"
#include "BotController.generated.h"


/**
 * 
 */
UCLASS()
class BOTGAME_API ABotController : public AAIController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Destination Marker")
	TSubclassOf<ADestinationMarker> DestinationMarkerClass;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UAISenseConfig_Sight* SightConfig;

private:
	class TQueue<ADestinationMarker*> QueuedDestinations;


public:

	ABotController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(Category = "Perception")
	virtual void OnPerceptionUpdated(TArray<AActor*> UpdatedActors);

	virtual void Possess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void EnqueueDestinationMarker(FVector Location, bool AddToQueue);

	//UFUNCTION(BlueprintCallable, Category = "AI")
	//ADestinationMarker* DequeueDestinationMarker();

	UFUNCTION(BlueprintCallable, Category = "AI")
	void DestroyDequeueDestinationMarker();

	UFUNCTION(BlueprintCallable, Category = "AI")
	bool IsDestinationQueueEmpty();

	UFUNCTION(BlueprintCallable, Category = "AI")
	ADestinationMarker* PeekDestinationQueue();

	UFUNCTION(BlueprintCallable, Category = "AI")
	ADestinationMarker* SpawnDestinationMarker(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void ClearDestinationQueue();

	UFUNCTION(BlueprintCallable, Category = "AI")
	class UAISenseConfig_Sight* GetSightConfig() const { return SightConfig; }
	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetSightConfig(class UAISenseConfig_Sight* val) { SightConfig = val; }

	UFUNCTION(BlueprintCallable, Category = "AI")
	class UAIPerceptionComponent* GetAIPerceptionComponent() const { return AIPerceptionComponent; }
	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetAIPerceptionComponent(class UAIPerceptionComponent* val) { AIPerceptionComponent = val; }
};
