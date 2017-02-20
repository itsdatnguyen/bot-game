// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "BotStruct.generated.h"

class ABot;
class AEquipment;

UENUM(BlueprintType)
enum class EAttackMethod : uint8
{
	AttackOnSight = 0,
	StopAttack = 1,
	PrioritizeTarget = 2,
	AttackOnlyTarget = 3
};

UENUM(BlueprintType)
enum class EEquipmentSpawnMethod : uint8
{
	SpawnWithDefaultEquipment = 0,
	SpawnWithoutDefaultEquipment = 1
};

USTRUCT(BlueprintType)
struct FBotStatStruct 
{
	GENERATED_BODY()


	
};

USTRUCT(BlueprintType)
struct FInt2DStruct
{
	GENERATED_BODY()

	FInt2DStruct() {
		X = 0;
		Y = 0;
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Integer")
	int X;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Integer")
	int Y;
};

USTRUCT(BlueprintType)
struct FChassisStatStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Chassis")
	FText ChassisName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Chassis")
	FInt2DStruct ChassisSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Chassis")
	int ChassisMaxWeight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Chassis")
	int ChassisBaseMovementSpeed;
};


USTRUCT(BlueprintType)
struct FPlayerMetaStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	FString SaveSlotName;

	// Cash accumilated by the player
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	int PlayerCash;

	// Only used when loading meta saves
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	bool DoesExist;

	FPlayerMetaStruct() {

	}
};

USTRUCT(BlueprintType)
struct FPlayerStatStruct
{
	GENERATED_BODY()

	// Equipment owned by the player that is not used by any bot
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	TMap<FString, int> PlayerEquipment;

	FPlayerStatStruct(){

	}
};

USTRUCT(BlueprintType)
struct FEquipmentClassRow
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TArray<TSubclassOf<AEquipment>> Columns;

	FEquipmentClassRow(){

	}

	void AddNewColumn(){
		Columns.Add(nullptr);
	}

	void AddNewColumn(TSubclassOf<AEquipment> Equipment) {
		Columns.Add(Equipment);
	}
};

USTRUCT(BlueprintType)
struct FEquipmentClassGrid
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Class")
	TArray<FEquipmentClassRow> Rows;

	FEquipmentClassGrid(){

	}

	void AddUninitialized(const int RowCount, const int ColCount){
		for (int32 v = 0; v < RowCount; v++) {
			AddNewRow();
			for (int32 b = 0; b < ColCount; b++) {
				Rows[v].AddNewColumn();
			}
		}
	}

	void ClearGrid(){
		TArray<FEquipmentClassRow> EmptyRow = TArray<FEquipmentClassRow>();
		Rows = EmptyRow;
	}

	void AddNewRow(){
		Rows.Add(FEquipmentClassRow());
	}
};

USTRUCT(BlueprintType)
struct FBotInstance
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Instance")
	FEquipmentClassGrid EquipmentClassGrid;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Instance")
	FChassisStatStruct ChassisStats;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Instance")
	TSubclassOf<ABot> BotClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Instance")
	FString BotName;

	FBotInstance(){

	}
};


USTRUCT(BlueprintType)
struct FEquipmentGridRow
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equipment")
	TArray<AEquipment*> Columns;

	FEquipmentGridRow()
	{

	}

	void AddNewColumn()
	{
		Columns.Add(nullptr);
	}
};

USTRUCT(BlueprintType)
struct FEquipmentGrid
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equipment")
	TArray<FEquipmentGridRow> Rows;

	FEquipmentGrid()
	{

	}

	void AddUninitialized(const int RowCount, const int ColCount)
	{
		for (int32 v = 0; v < RowCount; v++){
			AddNewRow();
			for (int32 b = 0; b < ColCount; b++){
				Rows[v].AddNewColumn();
			}
		}
	}

	void ClearGrid()
	{
		TArray<FEquipmentGridRow> EmptyRow = TArray<FEquipmentGridRow>();
		Rows = EmptyRow;
	}

	void AddNewRow()
	{
		Rows.Add(FEquipmentGridRow());
	}
};

USTRUCT(BlueprintType)
struct FEquipmentStatStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	int EquipmentHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	int EquipmentWeight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	int KineticRes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	int ExplosionRes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	int ElementRes;

	FEquipmentStatStruct()
	{
		EquipmentHealth = 0;
		EquipmentWeight = 0;
		KineticRes = 0;
		ExplosionRes = 0;
		ElementRes = 0;
	}
};

USTRUCT(BlueprintType)
struct FEquipmentPreviewStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	class UTexture2D* EquipmentImage;

	FEquipmentPreviewStruct()
	{
		
	}
};


/**
 * 
 */
UCLASS()
class BOTGAME_API UBotStruct : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
