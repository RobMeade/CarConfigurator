// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CarManufacturer.generated.h"


USTRUCT(BlueprintType)
struct FCarManufacturer
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere)
	FString Name;
};