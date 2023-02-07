// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "CarConfiguratorPlayerController.generated.h"


class ACarConfiguratorHUD;
class UCarConfiguratorOverlay;


/**
 *
 */
UCLASS()
class CARCONFIGURATOR_API ACarConfiguratorPlayerController : public APlayerController
{
	GENERATED_BODY()


public:

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;


protected:

	/** Called when the game starts */
	virtual void BeginPlay() override;

	/** Checks to see whether required objects can be used */
	void PollInitialized();


private:

	/** Sets input mode to UI only and shows mouse cursor */
	void SetUIInputMode();

	/** The heads up display where we will display the car configurator widgets */
	UPROPERTY()
	ACarConfiguratorHUD* CarConfiguratorHUD;

	/** The car configurator overlay widget which will be added to the HUD */
	UPROPERTY()
	UCarConfiguratorOverlay* CarConfiguratorOverlay;
};
