// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Equipment.h"
#include "Bot.generated.h"

UCLASS()
class BOTGAME_API ABot : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bot")
	class UChassisComponent* ChassisComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bot")
	FEquipmentGrid EquipmentGrid;

protected:
	float HighlightOpacity;

private:
	FString BotName;

	int PlayerId;

	int TeamId;

public:
	// Sets default values for this character's properties
	ABot();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	FVector2D GetEquipmentIndex(AEquipment* EquipmentToFind);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	AEquipment* ReplaceEquipment(AEquipment* EquipmentToReplace, TSubclassOf<AEquipment> NewEquipmentClass);

	// Enables or disables a hovered effect on the bot
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void UIHover(bool Status);

	// Enables or disables a selected effect on the bot
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void UISelect(bool Status);

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHighlightOpacity() const { return HighlightOpacity; }

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void DisableBot(bool Disable);

	// Will destroy the bot and its equipment
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void DestroyBot();

	// Getters and setters

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetBotName(FString Name) { BotName = Name; }

	UFUNCTION(BlueprintCallable, Category = "Grid")
	FString GetBotName() const { return BotName; }

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SetPlayerId(int Id) {if(Id >= 0) {PlayerId = Id;} }

	UFUNCTION(BlueprintCallable, Category = "Grid")
	int GetPlayerId() const { return PlayerId;}

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SetTeamId(int Id) {if(Id >= 0) {TeamId = Id;} }

	UFUNCTION(BlueprintCallable, Category = "Grid")
	int GetTeamId() const { return TeamId;}

private:
	void UpdateBotStats();
};
