// Copyright Rob Meade. All Rights Reserved.


#include "CarsData.h"


UCarsData::UCarsData()
{
	// ...
}

void UCarsData::InitializeData()
{
	InitializeManufacturers();
}

TArray<FCar> UCarsData::GetCars()
{
	return Cars;
}

void UCarsData::InitializeManufacturers()
{
	Manufacturers.Empty();

	if (Cars.Num() > 0)
	{
		for (auto& Car : Cars)
		{
			Manufacturers.AddUnique(Car.Manufacturer);
		}
	}
}

int32 UCarsData::GetTotalPriceForConfiguredCar(const FCar& ConfiguredCar) const
{
	int32 TotalPrice = 0;

	// model
	TotalPrice += ConfiguredCar.Model.BasePrice;

	// engine
	if (ConfiguredCar.Model.Engines.Num() > 0)
	{
		TotalPrice += ConfiguredCar.Model.Engines[0].Price;		
	}

	// color exterior
	if (ConfiguredCar.Model.ExteriorColors.Num() > 0)
	{
		TotalPrice += ConfiguredCar.Model.ExteriorColors[0].Price;		
	}

	// color interior
	if (ConfiguredCar.Model.InteriorColors.Num() > 0)
	{
		TotalPrice += ConfiguredCar.Model.InteriorColors[0].Price;		
	}

	return TotalPrice;
}

TArray<FCarManufacturer> UCarsData::GetManufacturers()
{
	return Manufacturers;
}

FCarManufacturer UCarsData::GetManufacturer(const FString& ManufacturerName)
{
	FCarManufacturer Result;

	if (Cars.Num() > 0)
	{
		for (auto& Manufacturer : GetManufacturers())
		{
			if (Manufacturer.Name == ManufacturerName)
			{
				Result = Manufacturer;
				break;
			}
		}
	}

	return Result;
}

TArray<FCarModel> UCarsData::GetModels(const FString& ManufacturerName) const
{
	TArray<FCarModel> Result;

	if (Cars.Num() > 0)
	{
		for (auto& Car : Cars)
		{
			if (Car.Manufacturer.Name == ManufacturerName)
			{
				Result.AddUnique(Car.Model);
			}
		}
	}

	return Result;
}

FCarModel UCarsData::GetModel(const FString& ModelName) const
{
	FCarModel Result;

	if (Cars.Num() > 0)
	{
		for (auto& Car : Cars)
		{
			if (Car.Model.Name == ModelName)
			{
				Result = Car.Model;
				break;
			}
		}
	}

	return Result;
}

FCarEngine UCarsData::GetEngine(const FString& ModelName, const FString& EngineName) const
{
	const FCarModel Model = GetModel(ModelName);
	FCarEngine Result;

	if (Cars.Num() > 0)
	{
		for (auto& Engine : Model.Engines)
		{
			if (Engine.Name == EngineName)
			{
				Result = Engine;
				break;
			}
		}
	}

	return Result;
}

FCarColorExterior UCarsData::GetExteriorColor(const FString& ModelName, const FString& ColorName) const
{
	const FCarModel Model = GetModel(ModelName);
	FCarColorExterior Result;

	if (Cars.Num() > 0)
	{
		for (auto& ExteriorColor : Model.ExteriorColors)
		{
			if (ExteriorColor.Name == ColorName)
			{
				Result = ExteriorColor;
				break;
			}
		}
	}

	return Result;
}

FCarColorInterior UCarsData::GetInteriorColor(const FString& ModelName, const FString& ColorName) const
{
	const FCarModel Model = GetModel(ModelName);
	FCarColorInterior Result;

	if (Cars.Num() > 0)
	{
		for (auto& InteriorColor : Model.InteriorColors)
		{
			if (InteriorColor.Name == ColorName)
			{
				Result = InteriorColor;
				break;
			}
		}
	}

	return Result;
}
