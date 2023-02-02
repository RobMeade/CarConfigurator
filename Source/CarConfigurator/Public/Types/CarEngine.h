// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CarEngineType.h"
#include "CarGearBoxType.h"

#include "CarEngine.generated.h"


USTRUCT(BlueprintType)
struct FCarEngine
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	FString Description;

	UPROPERTY(EditAnywhere)
	ECarEngineType EngineType;

	UPROPERTY(EditAnywhere)
	ECarGearBoxType GearBoxType;

	UPROPERTY(EditAnywhere)
	int32 Price;
};