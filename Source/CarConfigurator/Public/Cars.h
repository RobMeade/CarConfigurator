// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "Types/Car.h"

#include "Cars.generated.h"


UCLASS(Blueprintable)
class CARCONFIGURATOR_API UCars : public UObject
{
	GENERATED_BODY()


public:

	UCars();


protected:

	UPROPERTY(EditAnywhere)
	TArray<FCar> Cars;


private:
	
};
