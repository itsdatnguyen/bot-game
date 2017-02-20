// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Bot.h"
#include "PlayerCameraController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHitDelegate, FHitResult, Hit);

/**
 * 
 */
UCLASS()
class BOTGAME_API APlayerCameraController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Mouse")
	FHitDelegate LeftMousePressDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Mouse")
	FHitDelegate RightMousePressDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Mouse")
	FHitDelegate RightMouseHeldDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Mouse")
	FHitDelegate MouseWheelPressDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Mouse")
	FHitDelegate MouseWheelHeldDelegate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	int PlayerId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	int TeamId;

protected:
	AEquipment* SelectedEquipment;

	AEquipment* HoveredEquipment;

private:
	bool MultiSelect;

	bool RemoveSelect;

	bool CanSelect;

	TArray<ABot*> SelectedBots;

	TArray<ABot*> ControlledBots;

	// if less or equal to 0, that means player is holding down move click
	float CurrentTimeUntilHoldMove;
	// Holds the time required until player can hold move click
	float TimeUntilHoldMoveThreshold;

	// if less or equal to 0, that means player is holding down move click
	float CurrentTimeUntilHoldWheel;
	// Holds the time required until player can hold move click
	float TimeUntilHoldWheelThreshold;

public:

	APlayerCameraController();

	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupInputComponent() override;

	void AddToSelection(TArray<ABot*> Bots);

	void AddToSelection(ABot* Bot);

	void RemoveFromSelection(TArray<ABot*> Bots);

	void RemoveFromSelection(ABot* Bot);

	void ResetSelection();

	void UpdateSelection(TArray<ABot*> Bots);

	void UpdateSelection(ABot* Bot);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void DisableHoverSelection();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void AddControlledBot(ABot* Bot);

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetRemoveSelect() const { return RemoveSelect; }

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetMultiSelect() const { return MultiSelect; }

	UFUNCTION(BlueprintCallable, Category = "UI")
	TArray<ABot*> GetSelectedBots() const { return SelectedBots; }

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	TArray<ABot*> GetControlledBots() const { return ControlledBots; }

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetCanSelect(bool Value) { CanSelect = Value; }
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCanSelect() const { return CanSelect; }

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetSelectedEquipment(AEquipment* Value);
	UFUNCTION(BlueprintCallable, Category = "UI")
	AEquipment* GetSelectedEquipment() const { return SelectedEquipment; }

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetHoveredEquipment(AEquipment* Value);
	UFUNCTION(BlueprintCallable, Category = "UI")
	AEquipment* GetHoveredEquipment() const { return HoveredEquipment; }

private:

	void SelectEquipment(FHitResult Hit);

	void PanUp(float Value);

	void PanRight(float Value);

	void ZoomIn();
	void ZoomOut();

	void MultiSelectHeld();
	void MultiSelectReleased();

	void RemoveSelectHeld();
	void RemoveSelectReleased();

	void SelectHeld();
	void SelectReleased();

	void MoveHeld();
	void MoveReleased();
	void MoveAxis(float Value);

	void WheelHeld();
	void WheelAxis(float Value);
};
