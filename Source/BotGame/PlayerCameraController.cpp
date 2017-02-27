// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "PlayerCameraController.h"
#include "PlayerCameraPawn.h"
#include "BotController.h"
#include "PlayerHUD.h"
#include "BotGameModeBase.h"
#include "Bot.h"

APlayerCameraController::APlayerCameraController()
{
	TimeUntilHoldMoveThreshold = 0.3f;
	CurrentTimeUntilHoldMove = 0;

	TimeUntilHoldWheelThreshold = 0.3f;
	CurrentTimeUntilHoldWheel = 0;

	PlayerId = 0;
	TeamId = 0;

	MultiSelect = false;
	RemoveSelect = false;
	CanSelect = true;
}

void APlayerCameraController::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCameraController::Tick(float DeltaSeconds)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("seriously" + FString::SanitizeFloat(CurrentTimeUntilHoldMove)));
	Super::Tick(DeltaSeconds);
	if (CurrentTimeUntilHoldMove > 0) {
		CurrentTimeUntilHoldMove -= DeltaSeconds;
	}
	if (CurrentTimeUntilHoldWheel > 0) {
		CurrentTimeUntilHoldWheel -= DeltaSeconds;
	}
}

void APlayerCameraController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("CameraPanUp", this, &APlayerCameraController::PanUp);
	InputComponent->BindAxis("CameraPanRight", this, &APlayerCameraController::PanRight);
	InputComponent->BindAxis("MoveAxis", this, &APlayerCameraController::MoveAxis);
	InputComponent->BindAxis("WheelClickAxis", this, &APlayerCameraController::WheelAxis);

	InputComponent->BindAction("ZoomIn", EInputEvent::IE_Pressed, this, &APlayerCameraController::ZoomIn);
	InputComponent->BindAction("ZoomOut", EInputEvent::IE_Pressed, this, &APlayerCameraController::ZoomOut);
	
	InputComponent->BindAction("MultiSelect", EInputEvent::IE_Pressed, this, &APlayerCameraController::MultiSelectHeld);
	InputComponent->BindAction("MultiSelect", EInputEvent::IE_Released, this, &APlayerCameraController::MultiSelectReleased);

	InputComponent->BindAction("RemoveSelect", EInputEvent::IE_Pressed, this, &APlayerCameraController::RemoveSelectHeld);
	InputComponent->BindAction("RemoveSelect", EInputEvent::IE_Released, this, &APlayerCameraController::RemoveSelectReleased);

	InputComponent->BindAction("Select", EInputEvent::IE_Pressed, this, &APlayerCameraController::SelectHeld);
	InputComponent->BindAction("Select", EInputEvent::IE_Released, this, &APlayerCameraController::SelectReleased);

	InputComponent->BindAction("Move", EInputEvent::IE_Pressed, this, &APlayerCameraController::MoveHeld);
	InputComponent->BindAction("Move", EInputEvent::IE_Released, this, &APlayerCameraController::MoveReleased);

	InputComponent->BindAction("WheelClick", EInputEvent::IE_Pressed, this, &APlayerCameraController::WheelHeld);
}

void APlayerCameraController::AddToSelection(TArray<ABot*> Bots)
{
	for (ABot* Bot : Bots) {
		Bot->UISelect(true);
	}
	SelectedBots.Append(Bots);
}

void APlayerCameraController::AddToSelection(ABot * Bot)
{
	Bot->UISelect(true);
	SelectedBots.Add(Bot);
}

void APlayerCameraController::RemoveFromSelection(TArray<ABot*> Bots)
{
	for (ABot* Bot : Bots) {
		Bot->UISelect(false);
		SelectedBots.RemoveSingle(Bot);
	}
}

void APlayerCameraController::RemoveFromSelection(ABot * Bot)
{
	Bot->UISelect(false);
	SelectedBots.RemoveSingle(Bot);
}

void APlayerCameraController::ResetSelection()
{
	for (ABot* Bot : SelectedBots) {
		Bot->UISelect(false);
	}
	SelectedBots.Empty();
}

void APlayerCameraController::UpdateSelection(TArray<ABot*> Bots)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, Bots.Num() + " was just updated for selection.");

	/*for (ABot* Bot : Bots) {
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, Bot->GetFullName() + " was just updated for selection.");
	}*/

	if (MultiSelect) {
		for (ABot* Bot : Bots) {
			if (ControlledBots.Contains(Bot)) {
				AddToSelection(Bots);
			}
		}
	}
	else if (RemoveSelect) {
		for (ABot* Bot : Bots) {
			RemoveFromSelection(Bots);
		}
	}
	else {
		ResetSelection();
		for (ABot* Bot : Bots) {
			if (ControlledBots.Contains(Bot)) {
				AddToSelection(Bots);
			}
		}
	}

	/*for (ABot* Bot : SelectedBots) {
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, Bot->GetName() + " is currently selected.");
	}*/
}

void APlayerCameraController::UpdateSelection(ABot* Bot)
{
	if (MultiSelect) {
		if (ControlledBots.Contains(Bot)) {
			AddToSelection(Bot);
		}
	}
	else if (RemoveSelect) {
		RemoveFromSelection(Bot);
	}
	else {
		ResetSelection();
		if (ControlledBots.Contains(Bot)) {
			AddToSelection(Bot);
		}
	}
}

void APlayerCameraController::DisableHoverSelection()
{
	if (HoveredEquipment) {
		HoveredEquipment->SetEquipmentHighlight(false);		
	}	
	if (SelectedEquipment) {
		SelectedEquipment->SetEquipmentHighlight(false);	
	}
	HoveredEquipment = nullptr;
	SelectedEquipment = nullptr;
}

void APlayerCameraController::AddControlledBot(ABot* Bot)
{
	if (Bot) {
		ControlledBots.AddUnique(Bot);
	}
}

void APlayerCameraController::SelectEquipment(FHitResult Hit)
{
	if (Hit.Actor.IsValid()) {
		AEquipment* HitEquipment = Cast<AEquipment>(Hit.Actor.Get());

		// If the hit equipment is valid and it is not the currently selected equipment 
		if (HitEquipment != SelectedEquipment)
		{
			if (HitEquipment) {
				if (SelectedEquipment) {
					SelectedEquipment->SetEquipmentHighlight(false);
				}
				SelectedEquipment = HitEquipment;
				if (SelectedEquipment) {
					SelectedEquipment->SetEquipmentHighlight(true);
				}				
			}
			// else if the current selected equipment is valid and the current selected equipment is not equal to the hovered equipment
			else {
				if (SelectedEquipment != HoveredEquipment) {
					if (SelectedEquipment)
					{
						SelectedEquipment->SetEquipmentHighlight(false);
					}					
					SelectedEquipment = nullptr;
				}
			}
		}
	}
}

void APlayerCameraController::PanUp(float Value)
{
	APlayerCameraPawn* PlayerCameraPawn = Cast<APlayerCameraPawn>(GetPawn());
	if (PlayerCameraPawn) {
		PlayerCameraPawn->AddMovementInput(FVector(1, 0, 0), Value, false);
	}
}

void APlayerCameraController::PanRight(float Value)
{
	APlayerCameraPawn* PlayerCameraPawn = Cast<APlayerCameraPawn>(GetPawn());
	if (PlayerCameraPawn) {
		PlayerCameraPawn->AddMovementInput(FVector(0, 1, 0), Value, false);
	}
}

void APlayerCameraController::ZoomIn()
{
	APlayerCameraPawn* PlayerCameraPawn = Cast<APlayerCameraPawn>(GetPawn());
	if (PlayerCameraPawn) {
		PlayerCameraPawn->Zoom(-1);
	}
}

void APlayerCameraController::ZoomOut()
{
	APlayerCameraPawn* PlayerCameraPawn = Cast<APlayerCameraPawn>(GetPawn());
	if (PlayerCameraPawn) {
		PlayerCameraPawn->Zoom(1);
	}
}

void APlayerCameraController::MultiSelectHeld()
{
	MultiSelect = true;
}

void APlayerCameraController::MultiSelectReleased()
{
	MultiSelect = false;
}

void APlayerCameraController::RemoveSelectHeld()
{
	RemoveSelect = true;
}

void APlayerCameraController::RemoveSelectReleased()
{
	RemoveSelect = false;
}

void APlayerCameraController::SelectHeld()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Camera, true, HitResult);
	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("HEY!"));
	

	if (CanSelect) {
		APlayerHUD* PlayerHUD = Cast<APlayerHUD>(GetHUD());
		if (PlayerHUD) {
			PlayerHUD->ShowSelection(true);
		}
		SelectEquipment(HitResult);
	}
	// Broadcast to all binded functions after trying to select equipment
	LeftMousePressDelegate.Broadcast(HitResult);
}

void APlayerCameraController::SelectReleased()
{
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(GetHUD());
	if (PlayerHUD) {
		PlayerHUD->ShowSelection(false);
	}
}


void APlayerCameraController::MoveAxis(float Value)
{
	// A certain amount of time must be passed until 
	if (CurrentTimeUntilHoldMove <= 0.f) {

		if (Value >= 1) {
			// Broadcast Hit
			FHitResult HitResult;
			GetHitResultUnderCursor(ECC_Camera, true, HitResult);
			RightMouseHeldDelegate.Broadcast(HitResult);

			ABotGameModeBase* GameMode = Cast<ABotGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			if (GameMode) {
				for (ABot* Bot : SelectedBots) {
					ABotController* BotController = Cast<ABotController>(Bot->GetController());

					CurrentTimeUntilHoldMove = TimeUntilHoldMoveThreshold;
					if (BotController) {
						if (MultiSelect) {
							BotController->EnqueueDestinationMarker(HitResult.Location, true);
						}
						else {
							BotController->EnqueueDestinationMarker(HitResult.Location, false);
						}
					}
				}
			}
		}
	}
}

void APlayerCameraController::WheelHeld()
{
	CurrentTimeUntilHoldMove = TimeUntilHoldWheelThreshold;

	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Camera, true, HitResult);
	MouseWheelPressDelegate.Broadcast(HitResult);
}

void APlayerCameraController::WheelAxis(float Value)
{
	if (CurrentTimeUntilHoldWheel <= 0.f && Value > 0) {
		FHitResult HitResult;
		GetHitResultUnderCursor(ECC_Camera, true, HitResult);
		MouseWheelHeldDelegate.Broadcast(HitResult);
	}
}


void APlayerCameraController::MoveHeld()
{
	CurrentTimeUntilHoldMove = TimeUntilHoldMoveThreshold;

	// Broadcast Hit
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Camera, true, HitResult);
	RightMousePressDelegate.Broadcast(HitResult);

	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString("seriously" + FString::SanitizeFloat(CurrentTimeUntilHoldMove)));
	ABotGameModeBase* GameMode = Cast<ABotGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode) {
		for (ABot* Bot : SelectedBots) {
			ABotController* BotController = Cast<ABotController>(Bot->GetController());
			if (BotController) {
				if (MultiSelect) {
					BotController->EnqueueDestinationMarker(HitResult.Location, true);
				}
				else {
					BotController->EnqueueDestinationMarker(HitResult.Location, false);
				}					
			}
		}
	}
}

void APlayerCameraController::MoveReleased()
{
	//CurrentTimeUntilHoldMove = TimeUntilHoldMoveThreshold;
}

void APlayerCameraController::SetSelectedEquipment(AEquipment* Value)
{
	if (!Value && SelectedEquipment) {
		SelectedEquipment->SetEquipmentHighlight(false);
	}
	else {
		SelectedEquipment = Value;
	}
}

void APlayerCameraController::SetHoveredEquipment(AEquipment* Value)
{
	if (!Value && HoveredEquipment) {
		HoveredEquipment->SetEquipmentHighlight(false);
	}
	else {
		HoveredEquipment = Value;
	}
}