// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "Equipment.h"


// Sets default values
AEquipment::AEquipment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
	
}

// Called when the game starts or when spawned
void AEquipment::BeginPlay()
{
	Super::BeginPlay();
	//StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
	StaticMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
}

// Called every frame
void AEquipment::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AEquipment::DestroyEquipment()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("Todo. Implement Equipment destruction."));
	//@todo
}

void AEquipment::ReviveEquipment(float InitialHealth)
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("Todo. Implement Equipment revive."));
	//@todo
}

void AEquipment::SetEquipmentHighlight(bool Highlight)
{
	if (StaticMeshComponent) {
		if (Highlight) {
			StaticMeshComponent->SetScalarParameterValueOnMaterials(FName("Fresnel"), 2.f);
			//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("Added Fresnel to: " + this->GetName()));
		}
		else {
			StaticMeshComponent->SetScalarParameterValueOnMaterials(FName("Fresnel"), 0.f);
			//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("Removed Fresnel from: " + this->GetName()));
		}
	}
}

