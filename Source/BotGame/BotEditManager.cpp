// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "BotEditManager.h"
#include "BotEditPlatform.h"
#include "BotComponentInventory.h"
#include "BotEditWidget.h"
#include "PlayerHUD.h"
#include "TileStatics.h"
#include "Equipment.h"
#include "Bot.h"
#include "BotGameModeBase.h"
#include "BotGameInstance.h"
#include "PlayerCameraController.h"


// Sets default values
ABotEditManager::ABotEditManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABotEditManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnHelpers();

	if (BotEditPlatform) {
		FInt2DStruct Struct2D;
		Struct2D.X = 10;
		Struct2D.Y = 5;
		BotEditPlatform->ResizePlatform(Struct2D);
	}
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	if (PlayerHUD) {
		PlayerHUD->SetCanSelect(false);
	}
}

// Called every frame
void ABotEditManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ABotEditManager::SpawnNewEquipment(int Rows, int Columns, ABot* Bot)
{
	// hexagons are spawned in a grid-like fashion. The topmost row juts more to the left than the row beneath it
	// https://i.stack.imgur.com/WT34G.png is a good example of how hexagons are spawned
	// hexagons are spawned row by row starting from the top left

	// X IS ACTUALLY SWAPPED WITH Y
	// x represents y dimension and y represents x dimension
	
	// clear all existing equipment
	/*
	TArray<AActor*> ActorChildren = BotToEquipTo->Children;

	for (AActor* Actor : ActorChildren) {
		AEquipment* Equipment = Cast<AEquipment>(Actor);
		if (Equipment) {
			Equipment->Destroy(false, true);
		}
	}*/

	for (int y = 0; y < Bot->EquipmentGrid.Rows.Num(); y++) {
		for (int x = 0; x < Bot->EquipmentGrid.Rows[y].Columns.Num(); x++){
			Bot->EquipmentGrid.Rows[y].Columns[x]->Destroy(false, true);
		}
	}
	Bot->EquipmentGrid.ClearGrid();
	Bot->EquipmentGrid.AddUninitialized(Rows, Columns);

	float LeftX = (Rows * TileStatics::TileSpacingX) / -2;
	float TopY = (Columns * TileStatics::TileSpacingY) / 2;

	float CurrentX;
	float CurrentY;

	FRotator Rotation = Bot->GetActorRotation();
	FVector DefaultLocation = FVector(0, 0, 0);

	ESpawnActorCollisionHandlingMethod SpawnMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int y = 0; y < Rows; y++) {
		CurrentY = TopY - (TileStatics::TileSpacingY * y);
		for (int x = 0; x < Columns; x++) {
			if (y % 2 == 0) {
				CurrentX = LeftX + (TileStatics::TileSpacingX * x);
			}
			else {
				CurrentX = LeftX + (TileStatics::TileSpacingX / 2) + (TileStatics::TileSpacingX * x);
			}
			
			ABotGameModeBase* GameMode = Cast<ABotGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			if (GameMode) {
				AEquipment* NewEquipment = GameMode->SpawnEquipment(DefaultEquipmentClass, DefaultLocation, Rotation, SpawnMethod);

				FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
				NewEquipment->AttachToActor(Bot, AttachRules, FName());
				Bot->EquipmentGrid.Rows[y].Columns[x] = NewEquipment;
				//BotToEquipTo->Children.Add(NewEquipment);

				// flip x and y axis to make up for unreal engine 3d
				FVector RelativeLocation = FVector(CurrentY, CurrentX, 0);
				NewEquipment->SetActorRelativeLocation(RelativeLocation);
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("Fatal error. BotEditManager cannot access BotGameModeBase."));
			}
		}
	}
}

void ABotEditManager::SpawnHelpers()
{
	FActorSpawnParameters SpawnParams;
	FVector const Location(0, 0, 0);
	FRotator const Rotation(0, 0, 0);

	if (PlatformClass) {
		BotEditPlatform = Cast<ABotEditPlatform>(GetWorld()->SpawnActor(PlatformClass, &Location, &Rotation, SpawnParams));
	}
	
	if (InventoryClass){
		BotComponentInventory = Cast<ABotComponentInventory>(GetWorld()->SpawnActor(InventoryClass, &Location, &Rotation, SpawnParams));
	}

	if (WidgetClass) {
		BotEditWidget = CreateWidget<UBotEditWidget>(GetGameInstance(), WidgetClass);
		BotEditWidget->AddToViewport(0);
	}	
}

TArray<ABot*> ABotEditManager::ReloadLevel()
{
	APlayerCameraController* PlayerController = Cast<APlayerCameraController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerController->SetSelectedEquipment(nullptr);
	PlayerController->SetHoveredEquipment(nullptr);

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABot::StaticClass(), Actors);
	ABot* Bot;
	for (AActor* Actor : Actors) {
		Bot = Cast<ABot>(Actor);
		if (Bot) {
			Bot->DestroyBot();
		}
	}

	TArray<ABot*> NewBots;
	ABotGameModeBase* GameMode = Cast<ABotGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode) {
		TArray<FBotInstance> BotInstances = Cast<UBotGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->BotInstanceArray;

		FVector Location = FVector(0, 0, 300);
		FRotator Rotation = FRotator(0, 0, 0);
		for (FBotInstance BotInstance : BotInstances) {
			NewBots.Add(GameMode->SpawnBotFromInstance(BotInstance, Location, Rotation, EEquipmentSpawnMethod::SpawnWithDefaultEquipment, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
		}
	}
	return NewBots;
}