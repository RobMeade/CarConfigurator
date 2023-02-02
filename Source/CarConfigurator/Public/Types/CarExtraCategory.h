// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CarExtra.h"

#include "CarExtraCategory.generated.h"


USTRUCT(BlueprintType)
struct FCarExtraCategory
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	int32 Order;

	UPROPERTY(EditAnywhere)
	TArray<FCarExtra> Extras;
};