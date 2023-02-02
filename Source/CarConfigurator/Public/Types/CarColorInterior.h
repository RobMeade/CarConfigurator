// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CarColorInterior.generated.h"


USTRUCT(BlueprintType)
struct FCarColorInterior
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	int32 Price;
};