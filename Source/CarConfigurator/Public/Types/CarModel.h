// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CarColorExterior.h"
#include "CarColorInterior.h"
#include "CarEngine.h"
#include "CarExtraCategory.h"

#include "CarModel.generated.h"


USTRUCT(BlueprintType)
struct FCarModel
{
	GENERATED_BODY()


public:
	
	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	FString Description;

	UPROPERTY(EditAnywhere)
	int32 BasePrice;

	UPROPERTY(EditAnywhere)
	FCarEngine Engine;

	UPROPERTY(EditAnywhere)
	FCarColorExterior ColorExterior;

	UPROPERTY(EditAnywhere)
	FCarColorInterior ColorInterior;

	UPROPERTY(EditAnywhere)
	TArray<FCarExtraCategory> ExtraCategories;	
};
