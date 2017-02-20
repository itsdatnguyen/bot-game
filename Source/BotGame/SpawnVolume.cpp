// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "SpawnVolume.h"

ASpawnVolume::ASpawnVolume()
{
	IsPlayerSpawnVolume = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	
	if (StaticMesh) {
		StaticMesh->AttachTo(RootComponent, TEXT(""), EAttachLocation::SnapToTarget, false);

		static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectMesh(TEXT("/Game/Base/Meshes/Shapes/Cube.Cube"));
		// Find the object from a blueprint
		FString const MaterialLocationPlayer("/Game/Base/Materials/Shapes/Inst_PlayerSpawnVolume.Inst_PlayerSpawnVolume");
		FString const MaterialLocationEnemy("/Game/Base/Materials/Shapes/Inst_EnemySpawnVolume.Inst_EnemySpawnVolume");

		static ConstructorHelpers::FObjectFinder<UMaterialInstance> ObjectPlayer((const TCHAR*)(*MaterialLocationPlayer));
		static ConstructorHelpers::FObjectFinder<UMaterialInstance> ObjectEnemy((const TCHAR*)(*MaterialLocationEnemy));

		// set static mesh
		if (ObjectMesh.Object != NULL) {
			UStaticMesh* StaticMeshBP = (UStaticMesh*)ObjectMesh.Object;
			if (StaticMeshBP) {
				// set static mesh properties
				StaticMesh->SetStaticMesh(StaticMeshBP);
				StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
				StaticMesh->SetCanEverAffectNavigation(false);
				StaticMesh->bGenerateOverlapEvents = false;
			}
		}


		// create dynamic material and add it to mesh
		if (ObjectPlayer.Object != NULL && ObjectEnemy.Object != NULL) {
			PlayerMaterial = (UMaterialInstance*)ObjectPlayer.Object;
			EnemyMaterial = (UMaterialInstance*)ObjectEnemy.Object;

			if (PlayerMaterial && EnemyMaterial) {
				//UMaterialInstanceDynamic* MaterialDynamic = UMaterialInstanceDynamic::Create(FoundMaterial, this);
				UMaterialInstanceDynamic* MaterialDynamic = (UMaterialInstanceDynamic*)PlayerMaterial;
				StaticMesh->SetMaterial(0, MaterialDynamic);

				MaterialDynamic = (UMaterialInstanceDynamic*)EnemyMaterial;
				StaticMesh->SetMaterial(0, MaterialDynamic);
			}
		}
	}

	// set root component settings
	RootComponent->SetMobility(EComponentMobility::Movable);
}

void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

}

void ASpawnVolume::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	// set mesh scale
	FVector const Size = (GetBrushComponent()->Bounds.GetBox().Max - GetBrushComponent()->Bounds.GetBox().Min) / 100.f;
	if (StaticMesh) {
		FVector const Scale(Size.X, Size.Y, 0.05);
		StaticMesh->SetWorldScale3D(Scale);

		if (IsPlayerSpawnVolume && PlayerMaterial) {
			StaticMesh->SetMaterial(0, (UMaterialInstanceDynamic*)PlayerMaterial);
		}
		else{
			if (EnemyMaterial) {
				StaticMesh->SetMaterial(0, (UMaterialInstanceDynamic*)EnemyMaterial);
			}		
		}
	}
}

