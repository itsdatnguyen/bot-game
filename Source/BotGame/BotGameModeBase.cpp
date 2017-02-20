// Fill out your copyright notice in the Description page of Project Settings.


#include "BotGame.h"
#include "BotGameModeBase.h"
#include "Bot.h"
#include "BotPhysicsConstraintComponent.h"
#include "PlayerCameraPawn.h"
#include "PlayerCameraController.h"
#include "TileStatics.h"
#include "SaveGameManager.h"
#include "ChassisComponent.h"
#include "DefaultEquipment.h"
#include "Kismet/KismetMathLibrary.h"

#include "GameInstanceTest.h"

void ABotGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	// BP_BotGameModeBase implements the default classes
	//DefaultPawnClass = APlayerCamera::StaticClass();
	//PlayerControllerClass = APlayerCameraController::StaticClass();
}

void ABotGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool ABotGameModeBase::Is2DVectorInRectangle(FVector2D Point, FVector2D RectStart, FVector2D RectEnd)
{
	FVector2D min;
	FVector2D max;

	min.X = fminf(RectStart.X, RectEnd.X);
	min.Y = fminf(RectStart.Y, RectEnd.Y);

	max.X = fmaxf(RectStart.X, RectEnd.X);
	max.Y = fmaxf(RectStart.Y, RectEnd.Y);

	if (Point.X > min.X && Point.X < max.X) {
		if (Point.Y > min.Y && Point.Y < max.Y) {
			return true;
		}
	}

	return false;
}

ASaveGameManager* ABotGameModeBase::GetSaveGameManager()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SaveManagerClass, Actors);

	ASaveGameManager* SaveManager;
	if (Actors.Num() > 0) {
		SaveManager = Cast<ASaveGameManager>(Actors[0]);
	}
	else {
		FActorSpawnParameters SpawnParams;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector Location(0, 0, 0);
		FRotator Rotation(0, 0, 0);
		SaveManager = Cast<ASaveGameManager>(GetWorld()->SpawnActor(SaveManagerClass, &Location, &Rotation, SpawnParams));
	}
	return SaveManager;
}

void ABotGameModeBase::AddBot(ABot* BotToAdd)
{
	if (BotToAdd) {
		AllBots.Add(BotToAdd);
	}
}

ABot* ABotGameModeBase::SpawnBot(TSubclassOf<ABot> BotClass, FString BotName, FChassisStatStruct ChassisStats, FVector Location, FRotator Rotation, ESpawnActorCollisionHandlingMethod SpawnMethod)
{
	//FVector Location = FVector(0, 0, 69);

	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = SpawnMethod;

	ABot* SpawnedBot = Cast<ABot>(GetWorld()->SpawnActor(BotClass, &Location, &Rotation, SpawnParams));

	SpawnedBot->SetBotName(BotName);
	SpawnedBot->ChassisComponent->ChassisStats = ChassisStats;

	// Collisions
	SpawnedBot->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);

	AllBots.Add(SpawnedBot);
	return SpawnedBot;
}

AEquipment* ABotGameModeBase::SpawnEquipment(TSubclassOf<AEquipment> EquipmentClass, FVector Location, FRotator Rotation, ESpawnActorCollisionHandlingMethod SpawnMethod)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = SpawnMethod;

	AEquipment* SpawnedEquipment = Cast<AEquipment>(GetWorld()->SpawnActor(EquipmentClass, &Location, &Rotation, SpawnParams));
	return SpawnedEquipment;
}

ABot* ABotGameModeBase::SpawnBotFromInstance(FBotInstance BotInstance, FVector Location, FRotator Rotation, EEquipmentSpawnMethod EquipmentSpawnMethod, ESpawnActorCollisionHandlingMethod SpawnMethod)
{
	ABot* Bot = SpawnBot(BotInstance.BotClass, BotInstance.BotName, BotInstance.ChassisStats, Location, Rotation, SpawnMethod);

	if (Bot) {
		Bot->SpawnDefaultController();

		int Rows = Bot->ChassisComponent->ChassisStats.ChassisSize.Y;
		int Columns = Bot->ChassisComponent->ChassisStats.ChassisSize.X;

		Bot->EquipmentGrid.AddUninitialized(Rows, Columns);

		// Equipment will spawn from the top left row by row until the bottom right
		// LeftX is the x coordinate that the first equipment will spawn at 
		// TopY is the y coordinate that the first equipment will spawn at
		float LeftX = (Columns * TileStatics::TileSpacingX) / -2;
		float TopY = (Rows * TileStatics::TileSpacingY) / 2;

		float CurrentX;
		float CurrentY;	

		// Equipment must always spawn in its desired location
		SpawnMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// Counter used to determine equipment name
		int Counter = 0;
		TSubclassOf<AEquipment> EquipmentClass;
		FVector RelativeLocation;

		// Iterate through equipment grid
		for (int y = 0; y < Rows; y++) {
			CurrentY = TopY - (TileStatics::TileSpacingY * y);
			for (int x = 0; x < Columns; x++) {
				Counter++;
				if (y % 2 == 0) {
					CurrentX = LeftX + (TileStatics::TileSpacingX * x);
				}
				else {
					CurrentX = LeftX + (TileStatics::TileSpacingX / 2) + (TileStatics::TileSpacingX * x);
				}

				EquipmentClass = BotInstance.EquipmentClassGrid.Rows[y].Columns[x];
				RelativeLocation = FVector(CurrentY, CurrentX, 0);

				AEquipment* SpawnedEquipment;
				if (EquipmentSpawnMethod == EEquipmentSpawnMethod::SpawnWithoutDefaultEquipment) {
					SpawnedEquipment = SpawnEquipmentForInstance(Bot, EquipmentClass, Rotation, RelativeLocation);
					Bot->EquipmentGrid.Rows[y].Columns[x] = SpawnedEquipment;
				}	
				else {				
					SpawnedEquipment = SpawnEquipmentForInstance(Bot, EquipmentClass, Rotation, RelativeLocation);
					Bot->EquipmentGrid.Rows[y].Columns[x] = SpawnedEquipment;
				}

				if (SpawnedEquipment) {
					// Bot collision will not collide with its equipment
					// Setup collision
					Bot->GetCapsuleComponent()->MoveIgnoreActors.Add(SpawnedEquipment);
				}			
			}
		}
	}
	return Bot;
}


UBotPhysicsConstraintComponent * ABotGameModeBase::CreatePhysicsConstraintComponent(AActor * RootActor, AActor * AttachedActor, FName ConstraintName)
{
	UBotPhysicsConstraintComponent* ConstraintComponent = ConstructObject<UBotPhysicsConstraintComponent>(UBotPhysicsConstraintComponent::StaticClass(), this, ConstraintName);
	if (RootActor && AttachedActor) {
		if (ConstraintComponent) {
			ConstraintComponent->RegisterComponent();
			ConstraintComponent->AttachTo(RootActor->GetRootComponent(), FName(), EAttachLocation::SnapToTarget, false);
			ConstraintComponent->ConstraintActor1 = RootActor;
			ConstraintComponent->ConstraintActor2 = AttachedActor;

			GEngine->AddOnScreenDebugMessage(-1, 8, FColor::Red, FString("Root is: " + RootActor->GetName()));
			GEngine->AddOnScreenDebugMessage(-1, 8, FColor::Red, FString("Attached is: " + AttachedActor->GetName()));

			ConstraintComponent->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
			ConstraintComponent->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
			ConstraintComponent->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

			ConstraintComponent->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);

			ABot* Bot = Cast<ABot>(RootActor);
			if (Bot) {
				//Bot->ConstraintComponents.Add(ConstraintComponent);
			}
		}
	}
	return ConstraintComponent;
}

AEquipment* ABotGameModeBase::SpawnEquipmentForInstance(ABot* Bot, TSubclassOf<AEquipment> EquipmentClass, FRotator Rotation, FVector RelativeLocation)
{
	FVector DefaultLocation = FVector(0, 0, 0);
	AEquipment* NewEquipment = SpawnEquipment(EquipmentClass, DefaultLocation, Rotation, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	if (NewEquipment) {
		FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
		NewEquipment->AttachToActor(Bot, AttachRules, FName());

		// NewEquipment->AttachToActor(Bot, FName(), EAttachLocation::KeepRelativeOffset);
		// Flip x and y axis to make up for unreal engine 3d
		NewEquipment->SetActorRelativeLocation(RelativeLocation);	
	}
	return NewEquipment;
}

void ABotGameModeBase::SpawnGameInstanceTest(FPlayerMetaStruct PlayerMeta, FPlayerStatStruct PlayerStats, TArray<FBotInstance> BotInstanceArray)
{
	FVector Location = FVector(0, 0, 0);
	FRotator Rotation = FRotator(0, 0, 0);

	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AGameInstanceTest* Test = Cast<AGameInstanceTest>(GetWorld()->SpawnActor(AGameInstanceTest::StaticClass(), &Location, &Rotation, SpawnParams));

	Test->PlayerMeta = PlayerMeta;
	Test->PlayerStats = PlayerStats;
	Test->BotInstanceArray = BotInstanceArray;
}