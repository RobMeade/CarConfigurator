// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Types/Car.h"
#include "Types/CarManufacturer.h"

#include "CarsData.generated.h"


/**
 * Serves as the primary source of data for cars.  Provides helper functions to return specific data from the main source.
 */
UCLASS(Blueprintable)
class CARCONFIGURATOR_API UCarsData : public UObject
{
	GENERATED_BODY()


public:

	/** Default constructor */
	UCarsData();

	/** Populates arrays of unique data which will be used for getters */
	void InitializeData();

	/**
	 * Gets the cars, contains all cars data
	 *
	 * @return An array of cars, or, an empty TArray
	 */
	TArray<FCar> GetCars();

	/**
	 * Gets the unique manufacturers for the current data set
	 *
	 * @return An array of unique manufacturers, or, an empty TArray 
	 */
	TArray<FCarManufacturer> GetManufacturers();

	/**
	 * Gets the first manufacturer from Cars for the specified manufacturer name
	 *
	 * @param ManufacturerName The name of the manufacturer to return
	 *
	 * @return A manufacturer for the specified manufacturer name, or, an empty FCanManufacturer
	 */
	FCarManufacturer GetManufacturer(const FString& ManufacturerName);

	/**
	 * Gets the unique models for the specified manufacturer name
	 *
	 * @param ManufacturerName The name of the manufacturer to return models for
	 *
	 * @return An array of unique models for the specified manufacturer name, or, an empty TArray 
	 */
	TArray<FCarModel> GetModels(const FString& ManufacturerName) const;

	/**
	 * Gets the first matching model from Cars for the specified model name
	 *
	 * @param ModelName The name of the model to return
	 *
	 * @return A mode for the specified model name, or, an empty FCarModel 
	 */
	FCarModel GetModel(const FString& ModelName) const;

	/**
	 * Gets the first matching engine from Cars for the specified model name and engine name
	 *
	 * @param ModelName The name of the model to return the engine for, improves searching
	 * @param EngineName The name of the engine to return 
	 *
	 * @return An engine for the specified model name and engine name, or, an empty FCarEngine
	 */
	FCarEngine GetEngine(const FString& ModelName, const FString& EngineName) const;

	/**
	 * Gets the first matching exterior color from Cars for the specified model name and color name
	 *
	 * @param ModelName The name of the model to return the exterior color for, improves searching
	 * @param ColorName The name of the color to return
	 *
	 * @return An exterior color for the specified model name and color name, or, an empty FCarColorExterior
	 */
	FCarColorExterior GetExteriorColor(const FString& ModelName, const FString& ColorName) const;

	/**
	 * Gets the first matching interior color from Cars for the specified model name and color name
	 *
	 * @param ModelName The name of the model to return the interior color for, improves searching
	 * @param ColorName The name of the interior color to return
	 *
	 * @return An interior color for the specified model name and color name, or, an empty FCarColorInterior
	 */
	FCarColorInterior GetInteriorColor(const FString& ModelName, const FString& ColorName) const;

	/**
	 * Calculates the total prices for the specified configured car.
	 *
	 * @param ConfiguredCar The configured car to calculate the total price for
	 *
	 * @return The total price of the car as an int32
	 */
	int32 GetTotalPriceForConfiguredCar(const FCar& ConfiguredCar) const;


protected:


private:

	/** Iterates through Cars and extracts each unique manufacturer, adding it to the Manufacturers helper array */
	void InitializeManufacturers();

	/** The array of cars */
	UPROPERTY(EditAnywhere)
	TArray<FCar> Cars;

	/** An array of unique manufacturers, acts as a helper array to remove excessive looping of the main Cars array */
	UPROPERTY()
	TArray<FCarManufacturer> Manufacturers;

};
