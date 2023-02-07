// Copyright Rob Meade. All Rights Reserved.


#include "CarConfiguratorPlayerController.h"

#include "UI/CarConfiguratorHUD.h"
#include "UI/CarConfiguratorOverlay.h"


void ACarConfiguratorPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetUIInputMode();
}

void ACarConfiguratorPlayerController::SetUIInputMode()
{
	APlayerController::SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}

void ACarConfiguratorPlayerController::Tick(float DeltaTime)
{
	PollInitialized();
}

// TODO: Move this to the HUD, it can be responsible for displaying its own data

void ACarConfiguratorPlayerController::PollInitialized()
{
	if (CarConfiguratorOverlay == nullptr)
	{
		CarConfiguratorHUD = CarConfiguratorHUD == nullptr ? Cast<ACarConfiguratorHUD>(GetHUD()) : CarConfiguratorHUD;

		if (CarConfiguratorHUD && CarConfiguratorHUD->GetCarConfiguratorOverlay())
		{
			CarConfiguratorOverlay = CarConfiguratorHUD->GetCarConfiguratorOverlay();
			if (CarConfiguratorOverlay)
			{
				CarConfiguratorHUD->DisplayCarData();				
			}
		}
	}
}
