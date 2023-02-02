#pragma once

UENUM(BlueprintType)
enum class ECarEngineType : uint8
{
	ECET_Petrol UMETA(DisplayName = "Petrol"),
	ECET_Diesel UMETA(DisplayName = "Diesel"),
	ECET_Electic UMETA(DisplayName = "Electric"),
	ECET_Hybrid UMETA(DisplayName = "Hybrid"),

	ECET_MAX UMETA(Displayname = "Default MAX")
};