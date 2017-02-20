// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "BotController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Bot.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"
#include "BotGameModeBase.h"



ABotController::ABotController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	SetSightConfig(CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config")));
	AIPerceptionComponent->ConfigureSense(*GetSightConfig());
	AIPerceptionComponent->SetDominantSense(GetSightConfig()->GetSenseImplementation());
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ABotController::OnPerceptionUpdated);

	GetSightConfig()->PeripheralVisionAngleDegrees = 360.f;
	GetSightConfig()->DetectionByAffiliation.bDetectEnemies = true;
	GetSightConfig()->DetectionByAffiliation.bDetectFriendlies = true;
	GetSightConfig()->DetectionByAffiliation.bDetectNeutrals = true;
}

void ABotController::BeginPlay()
{
	Super::BeginPlay();
	//Destination = GetPawn()->GetActorLocation();
}

void ABotController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABotController::OnPerceptionUpdated(TArray<AActor*> UpdatedActors)
{

}

void ABotController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	/*if (InPawn) {

		ABot* PossessedBot = Cast<ABot>(GetPawn());
		if (PossessedBot) {
			//SightConfig->SightRadius = PossessedBot->GetCurrentStats().FireDistance;
			//SightConfig->LoseSightRadius = PossessedBot->GetCurrentStats().SightDistance;
			GetSightConfig()->PeripheralVisionAngleDegrees = 360.f;
			GetSightConfig()->DetectionByAffiliation.bDetectEnemies = true;
			GetSightConfig()->DetectionByAffiliation.bDetectFriendlies = true;
			GetSightConfig()->DetectionByAffiliation.bDetectNeutrals = true;
			AIPerceptionComponent->ConfigureSense(*GetSightConfig());
		}
	}*/
}

ADestinationMarker* ABotController::SpawnDestinationMarker(FVector Location)
{
	FActorSpawnParameters SpawnParams;
	FRotator const Rotation(0, 0, 0);

	ADestinationMarker* DestinationMarker = Cast<ADestinationMarker>(GetWorld()->SpawnActor(DestinationMarkerClass, &Location, &Rotation, SpawnParams));
	return DestinationMarker;
}

void ABotController::EnqueueDestinationMarker(FVector Location, bool AddToQueue)
{
	if (AddToQueue) {
		QueuedDestinations.Enqueue(SpawnDestinationMarker(Location));
	}
	else {
		ClearDestinationQueue();
		QueuedDestinations.Enqueue(SpawnDestinationMarker(Location));
	}
}

void ABotController::DestroyDequeueDestinationMarker()
{
	ADestinationMarker* Marker;
	QueuedDestinations.Dequeue(Marker);
	Marker->Destroy(false, true);
}

/*
ADestinationMarker* ABotController::DequeueDestinationMarker()
{
	// Do not use this function. Dequeuing means a reference to a destination marker is lost
	ADestinationMarker* Marker;
	QueuedDestinations.Dequeue(Marker);
	return Marker;
}*/

bool ABotController::IsDestinationQueueEmpty()
{
	return QueuedDestinations.IsEmpty();
}

ADestinationMarker* ABotController::PeekDestinationQueue()
{
	ADestinationMarker* PeekDestinationMarker;
	QueuedDestinations.Peek(PeekDestinationMarker);
	return PeekDestinationMarker;
}



void ABotController::ClearDestinationQueue()
{
	while (!QueuedDestinations.IsEmpty()) {
		ADestinationMarker* CurrentMarker;
		QueuedDestinations.Dequeue(CurrentMarker);
		CurrentMarker->Destroy(false, true);
	}
}
