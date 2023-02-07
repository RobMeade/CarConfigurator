// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CarColorExterior.h"
#include "CarColorInterior.h"
#include "CarEngine.h"
#include "CarExtraCategory.h"

#include "CarModel.generated.h"


/**
 *	A container for a model option for the car.  Can be used to hold all options relevant to the specific model, or, to hold configured options for a specific selection.
 */
USTRUCT(BlueprintType)
struct FCarModel
{
	GENERATED_BODY()


public:

	/**
	 *	Default constructor
	 */
	FCarModel() {};

	/**
	 *  Name equality operator
	 */
	bool operator==(const FCarModel& Other) const { return Name == Other.Name; }

	/**
	 *	The model's name
	 */
	UPROPERTY(EditAnywhere)
	FString Name;

	/**
	 *	The model's description
	 */
	UPROPERTY(EditAnywhere)
	FString Description;

	/**
	 *	The model's base price
	 */
	UPROPERTY(EditAnywhere)
	int32 BasePrice = 0;

	/**
	 *	The model's engines
	 */
	UPROPERTY(EditAnywhere)
	TArray<FCarEngine> Engines;

	/**
	 *	The model's exterior colors
	 */
	UPROPERTY(EditAnywhere)
	TArray<FCarColorExterior> ExteriorColors;

	/**
	 *	The model's interior colors
	 */
	UPROPERTY(EditAnywhere)
	TArray<FCarColorInterior> InteriorColors;

	/**
	 *	The model's extras categories
	 */
	UPROPERTY(EditAnywhere)
	TArray<FCarExtraCategory> ExtraCategories;	
};
