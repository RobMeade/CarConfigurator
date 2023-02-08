// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "CarsData.h"

#include "CarConfiguratorHUD.generated.h"


class UCarConfiguratorOverlay;
class UComboBoxString;
class UTexture2D;


/**
 * The heads up display, derived from the AHUD base class.
 *
 * The HUD manages the display of user widgets and all interactions for the car configurator overlay and the player.
 */
UCLASS()
class CARCONFIGURATOR_API ACarConfiguratorHUD : public AHUD
{
	GENERATED_BODY()


public:

	/** Displays car data using the overlay widget. Populates the manufacturers, available cars, and resets the configured car overlay */
	void DisplayCarData();

	/** Returns the CarConfigurationOverlay */
	FORCEINLINE UCarConfiguratorOverlay* GetCarConfiguratorOverlay() const { return CarConfiguratorOverlay; }


protected:

	/**
	 * Called when the game starts and this actor is spawned.  Adds widgets and binds delegates
	 */
	virtual void BeginPlay() override;


private:

	/** Our Blueprint class, acting as a data asset, enabling us to pass data into the HUD */
	UPROPERTY(EditAnywhere, Category = "Configurator")
	TSubclassOf<UCarsData> CarsData;

	/** The car configurator user widget class to create, used to display configuration options */
	UPROPERTY(EditAnywhere, Category = "Configurator")
	TSubclassOf<UUserWidget> CarConfiguratorOverlayClass;

	/** The configured car user widget class, used to display the configured car */
	UPROPERTY(EditAnywhere, Category = "Configurator")
	TSubclassOf<UUserWidget> ConfiguredCarOverlayClass;

	/** The configured car item user widget class, used to display configured car items */
	UPROPERTY(EditAnywhere, Category = "Configurator")
	TSubclassOf<UUserWidget> ConfiguredCarItemClass;

	/** The configured car item heading user widget class, used to display headings for configured car items */
	UPROPERTY(EditAnywhere, Category = "Configurator")
	TSubclassOf<UUserWidget> ConfiguredCarItemHeadingClass;

	/** The CarConfiguratorOverlay, used for binding to UI widgets */
	UPROPERTY()
	UCarConfiguratorOverlay* CarConfiguratorOverlay;

	/** Car is our primary data source object */
	UPROPERTY()
	UCarsData* Cars;

	/** A container for holding the configured car options, used within the ConfiguredCarOverlay when displaying information to the player */
	UPROPERTY()
	FCar ConfiguredCar;

	/** Adds the overlay widget to the viewport */
	void AddCarConfiguratorOverlay();

	/** Binds delegates for UI widget events */
	void BindDelegates();

	/**
	 * Delegate for selecting a manufacturer
	 *
	 * @param SelectedManufacturer The name of the manufacturer that was selected
	 * @param SelectionInfoType Additional information regarding the selection event
	 */
	UFUNCTION()
	void OnSelectManufacturer(const FString SelectedManufacturer, const ESelectInfo::Type SelectionInfoType);

	/**
	 * Delegate for selecting a model
	 *
	 * @param SelectedModel The name of the model that was selected
	 * @param SelectionInfoType Additional information regarding the selection event
	 */
	UFUNCTION()
	void OnSelectModel(const FString SelectedModel, const ESelectInfo::Type SelectionInfoType);

	/**
	 * Delegate for selecting an engine
	 *
	 * @param SelectedEngine The name of the engine that was selected
	 * @param SelectionInfoType Additional information regarding the selection event
	 */
	UFUNCTION()
	void OnSelectEngine(const FString SelectedEngine, const ESelectInfo::Type SelectionInfoType);

	/**
	 * Delegate for selecting an exterior color
	 *
	 * @param SelectedExteriorColor The name of the exterior color that was selected
	 * @param SelectionInfoType Additional information regarding the selection event
	 */
	UFUNCTION()
	void OnSelectExteriorColor(const FString SelectedExteriorColor, const ESelectInfo::Type SelectionInfoType);

	/**
	 * Delegate for selecting an interior color
	 *
	 * @param SelectedInteriorColor The name of the interior color that was selected
	 * @param SelectionInfoType Additional information regarding the selection event
	 */
	UFUNCTION()
	void OnSelectInteriorColor(const FString SelectedInteriorColor, const ESelectInfo::Type SelectionInfoType);

	/**
	 * Updates the number of available cars for selection, includes the number of cars, unique manufacturers, and unique models
	 *
	 * @param AvailableCars The number of available cars to display
	 * @param UniqueManufacturers The number of unique manufacturers to display
	 */
	void UpdateAvailableCars(const int32 AvailableCars, const int32 UniqueManufacturers) const;

	/**
	 * Updates the options within the manufacturers combobox
	 *
	 * @param Manufacturers A reference to the array of manufacturers
	 */
	void UpdateManufacturers(const TArray<FCarManufacturer>& Manufacturers) const;

	/**
	 * Updates the options within the models combobox
	 *
	 * @param Models A reference to the array of specific models
	 */
	void UpdateModels(const TArray<FCarModel>& Models) const;

	/**
	 * Updates the options within the engines combobox
	 *
	 * @param Engines A reference to the array of specific engines
	 */
	void UpdateEngines(const TArray<FCarEngine>& Engines) const;

	/**
	 * Updates the options within the colors exterior combobox
	 *
	 * @param ColorsExterior A reference to the array of specific exterior colors
	 */
	void UpdateColorsExterior(const TArray<FCarColorExterior>& ColorsExterior) const;

	/**
	 * Updates the options within the colors interior combobox
	 *
	 * @param ColorsInterior A reference to the array of specific interior colors
	 */
	void UpdateColorsInterior(const TArray<FCarColorInterior>& ColorsInterior) const;

	/**
	 * Resets the configured car overlay, sets the manufacturer for the configured car and updates options for the available models
	 *
	 * @param Manufacturer A reference to the specific manufacturer
	 */
	void SelectManufacturer(const FCarManufacturer& Manufacturer);

	/**
	 * Sets the model for the configured car and updates options for the available engines, exterior colors, and interior colors
	 *
	 * @param Model A reference to the specific model
	 */
	void SelectModel(const FCarModel& Model);

	/**
	 * Sets the engine for the configured car
	 *
	 * @param Engine A reference to the specific engine
	 */
	void SelectEngine(const FCarEngine& Engine);

	/**
	 * Sets the exterior color for the configured car
	 *
	 * @param ExteriorColor A reference to the specific color exterior
	 */
	void SelectExteriorColor(const FCarColorExterior& ExteriorColor);

	/**
	 * Sets the interior color for the configured car
	 *
	 * @param InteriorColor A reference to the specific color interior
	 */
	void SelectInteriorColor(const FCarColorInterior& InteriorColor);

	/**
	 * Shows or hides the model preview
	 *
	 * @param bShowModelPreview Indicates whether to show the model preview or not
	 */
	void ShowModelPreview(const bool bShowModelPreview) const;

	/*
	 * Sets the preview texture for the model preview image
	 *
	 * @param PreviewText The preview texture to set
	 */
	void UpdateModelPreview(UTexture2D* PreviewTexture) const;

	/**
	 * Sets the specified manufacturer for the configured car and updates the configured car overlay
	 *
	 * @param ManufacturerToConfigure A reference to the specific model to configure
	 */
	void SetConfiguredCarManufacturer(const FCarManufacturer& ManufacturerToConfigure);

	/**
	 * Sets the specified model for the configured car and updates the configured car overlay
	 *
	 * @param ModelToConfigure A reference to the specific model to configure
	 */
	void SetConfiguredCarModel(const FCarModel& ModelToConfigure);

	/**
	 * Sets the specified engine for the configured car and updates the configured car overlay
	 *
	 * @param EngineToConfigure A reference to the specific engine to configure
	 */
	void SetConfiguredCarEngine(const FCarEngine& EngineToConfigure);

	/**
	 * Sets the exterior color for the configured car and updates the configured car overlay
	 *
	 * @param ColorExteriorToConfigure A reference to the specific color exterior to configure
	 */
	void SetConfiguredCarExteriorColor(const FCarColorExterior& ColorExteriorToConfigure);

	/**
	 * Sets the interior color for the configured car and updates the configured car overlay
	 *
	 * @param ColorInteriorToConfigure A reference to the specific color interior to configure
	 */
	void SetConfiguredCarInteriorColor(const FCarColorInterior& ColorInteriorToConfigure);

	/** Resets the configured car overlay, displays all configured car items, and updates the total price */
	void UpdateConfiguredCar();

	/**
	 * Adds a heading to the configured car overlay to help separate configured items
	 *
	 * @param Name The name to be displayed in the heading
	 */
	void AddConfiguredCarItemHeading(const FString Name) const;

	/**
	 * Adds an item to the configured car overlay, displaying the name, price, and description.
	 * Overloaded versions of this function are available for scenarios where specific data does not need to be displayed.
	 *
	 * @param Name The name to be displayed
	 * @param Description The description to be display
	 * @param Price The price to be display
	 */
	void AddConfiguredCarItem(const FString& Name, const FString& Description, const int32& Price) const;

	/**
	 * Overload version of AddConfiguredCarItem to allow setting only the name and price, used for items which do not have a description (e.g. ExteriorColor)
	 *
	 * @param Name The name to be displayed
	 * @param Price The price to be displayed
	 */
	void AddConfiguredCarItem(const FString& Name, const int32& Price) const;

	/**
	 * Overloaded version of AddConfiguredCarItem to allow setting only the name, used for items which do not have a description or price (e.g. Manufacturer)
	 *
	 * @param Name The name to be displayed
	 */
	void AddConfiguredCarItem(const FString& Name) const;

	/**
	 * Resets the model preview, removing any set model textures
	 */
	void ResetModelPreview() const;

	/** Removes all items from the configured car overlay and resets the total price to zero */
	void ResetConfiguredCar() const;

	/**
	 * Adds the array of options to the combobox.
	 *
	 * If the Options array is not empty, the combobox is enabled and options are added.  The first option is set as the selected option.
	 *
	 * If the Options array is empty, the combobox is disabled.  An option is added, and selected, to indicate no options are available.
	 *
	 * @param ComboBox The combobox to add options to
	 * @param Options An array of options to add to the combobox
	 */
	template <typename T>
	void AddComboBoxOptions(UComboBoxString* ComboBox, const TArray<T>& Options) const;

	/**
	 * Removes all of the options from the specified combobox
	 *
	 * @param ComboBox The combobox to remove items from
	 */
	void ResetComboBox(UComboBoxString* ComboBox) const;

	/**
	 * Returns the specified price as formatted currency.
	 *
	 * @param Price The price to format as currency
	 */
	FText GetFormattedPrice(const int32& Price) const;

	/**
	 * Re-initializes the car configurator, resetting the model preview, and configured car overlay.
	 */
	void ReInitializeCarConfigurator();

	/**
	 * Delegate for taking a screenshot and opening the configured save screenshot directory.
	 */
	UFUNCTION()
	void TakeScreenShot();

	/**
	 * Delegate for quitting the game/application
	 *
	 * Note: Not the normal location for this functionality, but as this is a UI based game/application
	 * and we don't have anything else to clear up in the GameMode or PlayerController, this is ok
	 */
	UFUNCTION()
	void OnQuit();
};
