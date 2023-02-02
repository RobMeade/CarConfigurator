// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CarManufacturer.h"
#include "CarModel.h"

#include "Car.generated.h"


USTRUCT(BlueprintType)
struct FCar
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere)
	FCarManufacturer Manufacturer;

	UPROPERTY(EditAnywhere)
	FCarModel Model;
};