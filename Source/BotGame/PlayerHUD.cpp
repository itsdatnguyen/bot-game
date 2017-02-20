// Fill out your copyright notice in the Description page of Project Settings.

#include "BotGame.h"
#include "PlayerHUD.h"
#include "PlayerCameraController.h"
#include "BotGameModeBase.h"
#include "Bot.h"

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerHUD::DrawHUD()
{
	Super::DrawHUD();
	if (DrawSelection && CanSelect) {
		FVector ProjStartLocation = Project(GetStartSelect().Location);
		FVector ProjCurrentLocation = Project(GetCurrentSelect().Location);
		float ScreenWidth = ProjCurrentLocation.X - ProjStartLocation.X;
		float ScreenHeight = ProjCurrentLocation.Y - ProjStartLocation.Y;
		FLinearColor Color = FLinearColor(0.f, 1.f, 0.f, 0.1f);

		DrawRect(Color, ProjStartLocation.X, ProjStartLocation.Y, ScreenWidth, ScreenHeight);

		UpdateHUDSelectedBots();
	}
}

FVector2D APlayerHUD::ConvertLocationTo2D(FVector Location)
{
	FVector ProjectedLocation = Project(Location);
	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("Projected Location is: " + ProjectedLocation.ToString()));
	return FVector2D(ProjectedLocation.X, ProjectedLocation.Y);
}

FHitResult APlayerHUD::GetStartSelect()
{
	return StartHitResult;
}

FHitResult APlayerHUD::GetCurrentSelect()
{
	FHitResult HitResult = FHitResult();
	GetOwningPlayerController()->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, false, HitResult);
	return HitResult;
}

void APlayerHUD::ShowSelection(bool Show)
{
	if (Show) {
		DrawSelection = true;
		GetOwningPlayerController()->GetHitResultUnderCursor(ECC_Camera, false, StartHitResult);
	}
	else {
		if (DrawSelection) {
			APlayerCameraController* PlayerController = Cast<APlayerCameraController>(GetOwningPlayerController());
			if (PlayerController) {
				PlayerController->UpdateSelection(HUDSelectedBots);

				ABotGameModeBase* GameMode = Cast<ABotGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
				if (GameMode) {
					for (ABot* Bot : GameMode->GetAllBots()) {
						if (Bot) {
							Bot->UIHover(false);
						}					
					}
				}
			}
		}
		DrawSelection = false;
	}
}

void APlayerHUD::UpdateHUDSelectedBots()
{
	HUDSelectedBots.Empty();

	ABotGameModeBase* GameMode = Cast<ABotGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	for (ABot* Bot : GameMode->GetAllBots()) {
		FVector2D BotLocation = ConvertLocationTo2D(Bot->GetActorLocation());

		FVector2D RectangleStart = ConvertLocationTo2D(GetStartSelect().Location);
		FVector2D RectangleCurrent = ConvertLocationTo2D(GetCurrentSelect().Location);

		if (GameMode->Is2DVectorInRectangle(BotLocation, RectangleStart, RectangleCurrent)) {
			//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, Bot->GetName() + " was in the select rectangle.");
			HUDSelectedBots.Add(Bot);
			Bot->UIHover(true);

			/*for (ABot* Wow : HUDSelectedBots) {
				GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, Bot->GetName() + " is in the HUDSelectedBots TArray.");
			}*/
		}
		else {
			Bot->UIHover(false);
		}
	}
}