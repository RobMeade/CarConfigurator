#pragma once

UENUM(BlueprintType)
enum class ECarGearBoxType : uint8
{
	ECGT_Manual UMETA(DisplayName = "Manual"),
	ECGT_Automatic UMETA(DisplayName = "Automatic"),

	ECGT_MAX UMETA(Displayname = "Default MAX")
};