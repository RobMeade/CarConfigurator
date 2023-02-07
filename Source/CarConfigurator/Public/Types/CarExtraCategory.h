// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CarExtra.h"

#include "CarExtraCategory.generated.h"


/**
 * A container for related extra options for a car, which can be categorized.  Supports sorting by Order in addition to Name.
 */
USTRUCT(BlueprintType)
struct FCarExtraCategory
{
	GENERATED_BODY()


public:

	/** Default constructor */
	FCarExtraCategory() {};

	/** The category's name */
	UPROPERTY(EditAnywhere)
	FString Name;

	/** The category's order, used when ordering the categories for a model */
	UPROPERTY(EditAnywhere)
	int32 Order = 0;

	/** The array of extras for the category */
	UPROPERTY(EditAnywhere)
	TArray<FCarExtra> Extras;
};