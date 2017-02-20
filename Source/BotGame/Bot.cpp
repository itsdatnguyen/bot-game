// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "Bot.h"
#include "BotController.h"
#include "ChassisComponent.h"
#include "BotGameModeBase.h"


// Sets default values
ABot::ABot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HighlightOpacity = 0.0f;

	ChassisComponent = CreateDefaultSubobject<UChassisComponent>(TEXT("Chassis Component"));

	//MovementComponent = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("Movement Component"));

	PlayerId = 0;
	TeamId = 0;
}

// Called when the game starts or when spawned
void ABot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*

	UWorld* World = GetWorld();

	TArray<FHitResult> Hits;

	// This is how I was already handling movement, just a simple velocity vector multiplied by the elapsed time this tick
	// You may want to also set the "bSweep" parameter in MoveComponent() here, if your root actor has a collision shape
	// My root actor is just an empty dummy used for attaching other things, so I do not sweep it
	FVector Move(GetVelocity() * DeltaTime);
	RootComponent->MoveComponent(Move, GetActorRotation(), false);

	// The "attached_actors" array is a TArray of AActor* that I fill as things are being attached
	// There are other ways to get all attached actors if necessary
	AEquipment* Equipment;

	for (int y = 0; y < EquipmentGrid.Rows.Num(); y++) {
		for (int x = 0; x < EquipmentGrid.Rows[y].Columns.Num(); x++) {	
			Equipment = EquipmentGrid.Rows[y].Columns[x];
			if (Equipment) {

				// Get the root USceneComponent of the attached actor and cast it to a UPrimitiveComponent
				UPrimitiveComponent *Root = Cast<UPrimitiveComponent>(Equipment->GetRootComponent());

				// Start of move
				FVector Start(Root->GetComponentLocation());

				// Some collision parameters, not sure what they do, just initialize them to defaults
				FComponentQueryParams cqparams(TEXT("sweep_params"), Equipment);
				FCollisionResponseParams crparams;
				Root->InitSweepCollisionParams(cqparams, crparams);

				// Sweep the component and fill "hits" with the results
				World->ComponentSweepMulti(Hits, Root, Start, Start + Move, Root->GetComponentRotation(), cqparams);

				for (FHitResult HitResult : Hits) {
					DispatchBlockingHit(Root, HitResult.GetComponent(), false, HitResult);
					GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("HitEquipment: " + HitResult.Actor->GetName()));
				}

				if (Hits.Num())
				{
					// You can handle the hits here or save them and deal with them later, etc...
					// You could also call DispatchBlockingHit() here if you want your actor's "on_hit" method to be called
				}
			}
		}
	}
	*/
}

// Called to bind functionality to input
void ABot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector2D ABot::GetEquipmentIndex(AEquipment* EquipmentToFind)
{
	FVector2D Index = FVector2D(-1, -1);
	int RowIndex = 0;
	int ColumnIndex = 0;

	for (FEquipmentGridRow Row : EquipmentGrid.Rows) {
		if (Row.Columns.Find(EquipmentToFind, ColumnIndex)) {
			Index.X = ColumnIndex;
			Index.Y = RowIndex;
			return Index;
		}
		RowIndex++;
	}
	return Index;
}

AEquipment* ABot::ReplaceEquipment(AEquipment* EquipmentToReplace, TSubclassOf<AEquipment> NewEquipmentClass)
{
	FVector2D EquipmentIndex = GetEquipmentIndex(EquipmentToReplace);
	if (EquipmentIndex.X != -1.f && EquipmentIndex.Y != -1.f) {
		FVector EquipmentLocation = EquipmentToReplace->GetActorLocation();
		FRotator EquipmentRotation = EquipmentToReplace->GetActorRotation();
		EquipmentToReplace->Destroy(false, true);

		ABotGameModeBase* GameMode = Cast<ABotGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		ESpawnActorCollisionHandlingMethod SpawnMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if (GameMode) {
			AEquipment* NewEquipment = GameMode->SpawnEquipment(NewEquipmentClass, EquipmentLocation, EquipmentRotation, SpawnMethod);

			FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);
			NewEquipment->AttachToActor(this, AttachRules, FName());
			EquipmentGrid.Rows[EquipmentIndex.Y].Columns[EquipmentIndex.X] = NewEquipment;
			return NewEquipment;
		}
	}
	return nullptr;
}

void ABot::UISelect(bool Status)
{
	if (Status) {
		HighlightOpacity = 1.f;
	}
	else {
		if (HighlightOpacity != 0.8f) {
			HighlightOpacity = 0;
		}
	}
}

void ABot::UIHover(bool Status)
{
	if (Status) {
		if (HighlightOpacity != 1.f) {
			HighlightOpacity = 0.8f;
		}
	}
	else {
		if (HighlightOpacity != 1.f) {
			HighlightOpacity = 0;
		}
	}
}

void ABot::DisableBot(bool Disable)
{
	SetActorHiddenInGame(Disable);
	SetActorEnableCollision(!Disable);
	SetActorTickEnabled(!Disable);

	for (int y = 0; y < EquipmentGrid.Rows.Num(); y++) {
		for (int x = 0; x < EquipmentGrid.Rows[y].Columns.Num(); x++) {
			AEquipment* CurrentEquip = EquipmentGrid.Rows[y].Columns[x];
			if (CurrentEquip) {
				//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("Disabled equipment part: " + CurrentEquip->GetName()));
				CurrentEquip->SetActorHiddenInGame(Disable);
				CurrentEquip->SetActorEnableCollision(!Disable);
			}		
		}
	}
}

void ABot::DestroyBot()
{
	AEquipment* Equipment;
	for (int y = 0; y < EquipmentGrid.Rows.Num(); y++) {
		for (int x = 0; x < EquipmentGrid.Rows[y].Columns.Num(); x++) {
			Equipment = EquipmentGrid.Rows[y].Columns[x];
			if (Equipment) {
				Equipment->Destroy(false, true);
			}
		}
	}
	Destroy(false, true);
}

void ABot::UpdateBotStats()
{

}