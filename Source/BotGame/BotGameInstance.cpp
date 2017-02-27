// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "BotGameInstance.h"
#include "ChassisComponent.h"
#include "Bot.h"
#include "SaveGameManager.h"

void UBotGameInstance::AddBotInstance(ABot* BotActor)
{
	if (BotActor) {
		FBotInstance NewBotInstance;
		NewBotInstance.ChassisStats = BotActor->ChassisComponent->ChassisStats;
		NewBotInstance.BotClass = BotActor->GetClass();
		NewBotInstance.BotName = BotActor->GetBotName();

		int Rows = BotActor->ChassisComponent->ChassisStats.ChassisSize.Y;
		int Columns = BotActor->ChassisComponent->ChassisStats.ChassisSize.X;

		NewBotInstance.EquipmentClassGrid.AddUninitialized(Rows, Columns);
		// iterate through the equipment of the bot and turn that into a 2d array of classes
		for (int y = 0; y < Rows; y++) {
			for (int x = 0; x < Columns; x++) {
				AEquipment* CurrentEquipment = BotActor->EquipmentGrid.Rows[y].Columns[x];
				if (CurrentEquipment) {
					NewBotInstance.EquipmentClassGrid.Rows[y].Columns[x] = CurrentEquipment->GetClass();
				}
			}
		}	
		BotInstanceArray.Add(NewBotInstance);
	}
}

void UBotGameInstance::UpdateBotInstance(TArray<ABot*> BotsToUpdate, bool OverwriteExisting)
{
	if (OverwriteExisting) {
		BotInstanceArray.Empty();
	}

	for (ABot* Bot : BotsToUpdate) {
		if (Bot) {
			AddBotInstance(Bot);
		}
	}
}

void UBotGameInstance::UpdateBotInstances(TArray<AActor*> BotsToUpdate, bool OverwriteExisting)
{
	if (OverwriteExisting) {
		BotInstanceArray.Empty();
	}
	
	for (AActor* Actor : BotsToUpdate) {
		ABot* Bot = Cast<ABot>(Actor);
		if (Bot) {
			AddBotInstance(Bot);
		}
	}
}

void UBotGameInstance::AddSelectedBotIndices(int Index)
{
	if (Index >= 0) {
		SelectedBotIndices.Add(Index);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Error, AddSelectedBotIndices parameter is lower than 0."));
	}
}