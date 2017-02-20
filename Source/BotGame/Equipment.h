// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BotStruct.h"
#include "Equipment.generated.h"


UCLASS()
class BOTGAME_API AEquipment : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	FEquipmentPreviewStruct PreviewStruct;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	FEquipmentStatStruct BaseStats;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	FEquipmentStatStruct CurrentStats;

private:
	ABot* BotOwner;

	FString EquipmentName;

	int EquipmentValue;

	bool IsDestroyed;

public:	
	// Sets default values for this actor's properties
	AEquipment();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
		
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void DestroyEquipment();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ReviveEquipment(float InitialHealth);

	UFUNCTION(BlueprintCallable, Category = "Bots")
	void SetBotOwner(ABot* NewOwner) {if(NewOwner){BotOwner = NewOwner;} }

	UFUNCTION(BlueprintCallable, Category = "Stats")
	ABot* GetBotOwner() const {return BotOwner;}

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetEquipmentName(FString Name) { EquipmentName = Name; }

	UFUNCTION(BlueprintCallable, Category = "Stats")
	FString GetEquipmentName() const { return EquipmentName; }

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetEquipmentValue(int Value) { if(Value > 0) { EquipmentValue = Value; } }

	UFUNCTION(BlueprintCallable, Category = "Stats")
	int GetEquipmentValue() const { return EquipmentValue; }

	UFUNCTION(BlueprintCallable, Category = "Material")
	void SetEquipmentHighlight(bool Highlight);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool GetIsDestroyed() const { return IsDestroyed;}
};
