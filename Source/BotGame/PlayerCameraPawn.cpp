// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "PlayerCameraPawn.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APlayerCameraPawn::APlayerCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ZoomLevels = 4;
	CurrentZoomLevel = 0;
	ZoomPerLevel = 180;
	DefaultHeight = 1600;
	PanSpeed = 125;
	InterpSpeed = 10;

	AutoPossessAI = EAutoPossessAI::Disabled;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	//CameraComponent->SetWorldRotation(FRotator(-180, -110, 0));
}

// Called when the game starts or when spawned
void APlayerCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	//CameraComponent->SetWorldRotation(FRotator(-180, -110, 0));
}

// Called every frame
void APlayerCameraPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	InterpCamera();
}

// Called to bind functionality to input
void APlayerCameraPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void APlayerCameraPawn::Zoom(int Value)
{
	CurrentZoomLevel += Value;
	CurrentZoomLevel = UKismetMathLibrary::Clamp(CurrentZoomLevel, -ZoomLevels, ZoomLevels);
}

void APlayerCameraPawn::InterpCamera()
{
	FVector CurrentLocation = GetActorLocation();
	FVector DesiredLocation = FVector(CurrentLocation.X, CurrentLocation.Y, DefaultHeight + CurrentZoomLevel * ZoomPerLevel) + ConsumeMovementInputVector() * PanSpeed;
	SetActorLocation(UKismetMathLibrary::VInterpTo(GetActorLocation(), DesiredLocation, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), InterpSpeed));


}