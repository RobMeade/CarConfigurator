// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "CarConfiguratorOverlay.generated.h"


class UButton;
class UComboBoxString;
class UImage;
class UTextBlock;

class UConfiguredCarOverlay;


/**
 * Base class for the car configurator overlay and responsible for binding widgets.
 *
 * Supports the display of information related to the car configurator.
 */
UCLASS()
class CARCONFIGURATOR_API UCarConfiguratorOverlay : public UUserWidget
{
	GENERATED_BODY()


public:

	/* Used to display the number of available cars in the configurator */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AvailableCars;

	/** Used to display all manufacturer options and enable the selection of a specific manufacturer */
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* Manufacturers;

	/** Used to display all model options for a specific manufacturer, and enable the selection of a specific model */
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* Models;

	/** Used to display all engine options for a specific model, and enable the selection of a specific engine */
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* Engines;

	/** Used to display all exterior color options for a specific mode, and enable the selection of a specific exterior color */
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ColorsExterior;

	/** Used to display all interior color options for a specific mode, and enable the selection of a specific interior color */
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ColorsInterior;

	/** Used to display a preview of the selected model and exterior color */
	UPROPERTY(meta = (BindWidget))
	UImage* ModelPreview;

	/** Used to display the configured car data, that is, the options that the player has already chosen */
	UPROPERTY(meta = (BindWidget))
	UConfiguredCarOverlay* ConfiguredCarOverlay;

	/** Used to quit the game */
	UPROPERTY(meta = (BindWidget))
	UButton* Quit;

	// TEMP - Testing
	UPROPERTY(meta = (BindWidget))
	UButton* ScreenShot;


protected:


private:

};
