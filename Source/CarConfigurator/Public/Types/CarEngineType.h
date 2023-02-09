// Copyright Rob Meade. All Rights Reserved.

#pragma once

/** Enum used to describe the type of engine */
UENUM(BlueprintType)
enum class ECarEngineType : uint8
{
	/** Combustion engine using petrol as fuel */
	ECET_Petrol UMETA(DisplayName = "Petrol"),
	/** Combustion engine using diesel as fuel */
	ECET_Diesel UMETA(DisplayName = "Diesel"),
	/** Electric motor instead of combustion engine */
	ECET_Electric UMETA(DisplayName = "Electric"),
	/** Combustion engine and electric motor */
	ECET_Hybrid UMETA(DisplayName = "Hybrid"),

	NUM UMETA(Hidden)
};