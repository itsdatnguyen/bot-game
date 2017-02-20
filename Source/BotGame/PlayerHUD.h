// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class BOTGAME_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	bool DrawSelection = false;

	UPROPERTY()
	bool CanSelect = true;

	UPROPERTY()
	FHitResult StartHitResult;
	
	UPROPERTY()
	TArray<ABot*> HUDSelectedBots;


public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void DrawHUD() override;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	FVector2D ConvertLocationTo2D(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "UI")
	FHitResult GetStartSelect();

	UFUNCTION(BlueprintCallable, Category = "UI")
	FHitResult GetCurrentSelect();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowSelection(bool Show);

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetDrawSelection() const { return DrawSelection; }

	UFUNCTION(BlueprintCallable, Category = "UI")
	TArray<ABot *> GetHUDSelectedBots() const { return HUDSelectedBots; }

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCanSelect() const { return CanSelect; }
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetCanSelect(bool val) { CanSelect = val; }
private:
	void UpdateHUDSelectedBots();
};
