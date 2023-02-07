// Copyright Rob Meade. All Rights Reserved.

#pragma once

/** Enum used to describe what type of gearbox an engine has */
UENUM(BlueprintType)
enum class ECarGearBoxType : uint8
{
	/** Manual transmission */
	ECGT_Manual UMETA(DisplayName = "Manual"),
	/** Automatic transmission */
	ECGT_Automatic UMETA(DisplayName = "Automatic"),
};