// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CarExtra.generated.h"


/**
 * A simple container for extra option for the car
 */
USTRUCT(BlueprintType)
struct FCarExtra
{
	GENERATED_BODY()


public:

	/** Default constructor */
	FCarExtra() {};

	/** The extra's name */
	UPROPERTY(EditAnywhere)
	FString Name;

	/** The extra's price, this value is added to the model's base price */
	UPROPERTY(EditAnywhere)
	int32 Price = 0;
};