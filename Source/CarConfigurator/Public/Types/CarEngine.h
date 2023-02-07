// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CarEngineType.h"
#include "CarGearBoxType.h"

#include "CarEngine.generated.h"


/**
 *	A simple container for an engine option for the car
 */
USTRUCT(BlueprintType)
struct FCarEngine
{
	GENERATED_BODY()


public:

	/**
	 *	Default constructor
	 */
	FCarEngine() {};

	/**
	 *	The engine's name
	 */
	UPROPERTY(EditAnywhere)
	FString Name;

	/**
	 *	The engine's description
	 */
	UPROPERTY(EditAnywhere)
	FString Description;

	/**
	 *	The engine's type
	 */
	UPROPERTY(EditAnywhere)
	ECarEngineType EngineType = ECarEngineType::ECET_Petrol;

	/**
	 *	The engine's gearbox type
	 */
	UPROPERTY(EditAnywhere)
	ECarGearBoxType GearBoxType = ECarGearBoxType::ECGT_Manual;

	/**
	 *	The engine's price, this value is added to the model's base price
	 */
	UPROPERTY(EditAnywhere)
	int32 Price = 0;
};