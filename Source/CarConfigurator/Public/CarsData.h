// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Types/Car.h"
#include "Types/CarManufacturer.h"

#include "CarsData.generated.h"


/**
 *	Serves as the primary source of data for cars.  Provides helper functions to return specific data from the main source.
 */
UCLASS(Blueprintable)
class CARCONFIGURATOR_API UCarsData : public UObject
{
	GENERATED_BODY()


public:

	/**
	 *	Default constructor
	 */
	UCarsData();

	/**
	 *	Populates arrays of unique data which will be used for getters
	 */
	void InitializeData();

	/**
	 *	Gets the cars, contains all cars data
	 *
	 *	@return	An array of FCar
	 */
	TArray<FCar> GetCars();

	/**
	 *	Gets the unique manufacturers for the current data set
	 *
	 *  @return	An array of unique FCarManufacturers 
	 */
	TArray<FCarManufacturer> GetManufacturers();

	/**
	 *	Gets the first manufacturer from Cars for the specified manufacturer name
	 *
	 *	@param ManufacturerName	The name of the manufacturer to return
	 *
	 *	@return An FCarManufacturer
	 */
	FCarManufacturer GetManufacturer(const FString& ManufacturerName);

	/**
	 *	Gets the unique models for the specified manufacturer name
	 *
	 *  @return	An array of unique FCarModels 
	 */
	TArray<FCarModel> GetModels(const FString& ManufacturerName) const;

	/**
	 *	Gets the first matching model from Cars for the specified model name
	 *
	 *  @return	An FCarModel 
	 */
	FCarModel GetModel(const FString& ModelName) const;

	/**
	 *	Gets the first matching engine from Cars for the specified model name and engine name
	 *
	 *	@return An FCarEngine
	 */
	FCarEngine GetEngine(const FString& ModelName, const FString& EngineName) const;

	/**
	 *	Gets the first matching exterior color from Cars for the specified model name and color name
	 *
	 *	@return An FCarColorExterior
	 */
	FCarColorExterior GetExteriorColor(const FString& ModelName, const FString& ColorName) const;

	/**
	 *	Gets the first matching interior color from Cars for the specified model name and color name
	 *
	 *	@return An FCarColorInterior
	 */
	FCarColorInterior GetInteriorColor(const FString& ModelName, const FString& ColorName) const;

	/**
	 *	Calculates the total prices for the specified configured car.
	 *
	 *	@param	ConfiguredCar	The configured car to calculate the total price for
	 *
	 *	@return	The total price of the car as an int32
	 */
	int32 GetTotalPriceForConfiguredCar(const FCar& ConfiguredCar) const;


protected:


private:

	/**
	 *	Iterates through Cars and extracts each unique manufacturer, adding it to the Manufacturers helper array
	 */
	void InitializeManufacturers();

	/**
	 *	The array of cars
	 */
	UPROPERTY(EditAnywhere)
	TArray<FCar> Cars;

	/**
	 *	An array of unique manufacturers, acts as a helper array to remove excessive looping of the main Cars array
	 */
	UPROPERTY()
	TArray<FCarManufacturer> Manufacturers;

};
