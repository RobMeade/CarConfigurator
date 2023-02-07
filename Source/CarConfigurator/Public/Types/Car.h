// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CarManufacturer.h"
#include "CarModel.h"

#include "Car.generated.h"


/**
 *	A representation of a real world car for use within the product configurator tool
 */
USTRUCT(BlueprintType)
struct FCar
{
	GENERATED_BODY()


public:

	/**
	 *	Default constructor
	 */
	FCar() {};

	/**
	 *	The car's manufacturer
	 */
	UPROPERTY(EditAnywhere)
	FCarManufacturer Manufacturer;

	/**
	 *	The car's model
	 */
	UPROPERTY(EditAnywhere)
	FCarModel Model;
};