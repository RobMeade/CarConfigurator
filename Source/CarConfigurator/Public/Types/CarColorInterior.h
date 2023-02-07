// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CarColorInterior.generated.h"


/**
 *	A simple container for an interior color option for the car
 */
USTRUCT(BlueprintType)
struct FCarColorInterior
{
	GENERATED_BODY()


public:

	/**
	 *	Default constructor
	 */
	FCarColorInterior() {};

	/**
	 *	The color interior's name
	 */
	UPROPERTY(EditAnywhere)
	FString Name;

	/**
	 *	The color interior's price, this value is added to the model's base price
	 */
	UPROPERTY(EditAnywhere)
	int32 Price = 0;
};