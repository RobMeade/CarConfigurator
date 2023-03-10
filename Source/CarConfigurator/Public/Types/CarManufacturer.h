// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "Templates/Function.h"

#include "CarManufacturer.generated.h"


/**
 * A simple container for a manufacturer option for the car
 */
USTRUCT(BlueprintType)
struct FCarManufacturer
{
	GENERATED_BODY()


public:

	/** Default constructor */
	FCarManufacturer() {};

	/**
	 * Name equality operator
	 *
	 * @param Other The other manufacturer, used to compare names
	 *
	 * @return True or false depending on whether the names match
	 */
	bool operator==(const FCarManufacturer& Other) const { return Name == Other.Name; }

	/** The manufacturers name */
	UPROPERTY(EditAnywhere)
	FString Name;
};