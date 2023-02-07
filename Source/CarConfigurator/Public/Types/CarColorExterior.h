// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CarColorExterior.generated.h"


/**
 *	A simple container for an exterior color option for the car
 */
USTRUCT(BlueprintType)
struct FCarColorExterior
{
	GENERATED_BODY()


public:

	/**
	 *	Default constructor
	 */
	FCarColorExterior() {};

	/**
	 *	The color exterior's name
	 */
	UPROPERTY(EditAnywhere)
	FString Name;

	/**
	 *	The color exterior's price, this value is added to the model's base price
	 */
	UPROPERTY(EditAnywhere)
	int32 Price = 0;
};