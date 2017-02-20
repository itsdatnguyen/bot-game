// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PlayerCameraPawn.generated.h"

UCLASS()
class BOTGAME_API APlayerCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* CameraComponent;

private:
	int ZoomLevels;

	int CurrentZoomLevel;

	int ZoomPerLevel;

	int DefaultHeight;

	int InterpSpeed;

	int PanSpeed;

public:
	// Sets default values for this pawn's properties
	APlayerCameraPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Zoom the camera in or out
	void Zoom(int Value);

private:
	void InterpCamera();


	
};
