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
	FCarEngine Result;

	const FCarModel Model = GetModel(ModelName);

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

TArray<FCarEngine> UCarsData::GetEnginesFiltered(const FString& ModelName, const TArray<ECarEngineType>& EngineTypeFilters, const TArray<ECarGearBoxType>& GearBoxTypeFilters) const
{
	TArray<FCarEngine> Result;

	const FCarModel Model = GetModel(ModelName);

	constexpr int32 NumberOfCarEngineTypes = static_cast<int32>(ECarEngineType::NUM);
	constexpr int32 NumberOfCarGearBoxTypes = static_cast<int32>(ECarGearBoxType::NUM);

	// no filters or all filters, in either case, return all engines for the specific model
	if (EngineTypeFilters.Num() == 0 && GearBoxTypeFilters.Num() == 0 || EngineTypeFilters.Num() == NumberOfCarEngineTypes && GearBoxTypeFilters.Num() == NumberOfCarGearBoxTypes)
	{
		Result = Model.Engines;
		return Result;
	}

	for (auto& Engine : Model.Engines)
	{
		// only compare engine types
		if (EngineTypeFilters.Num() > 0 && GearBoxTypeFilters.Num() == 0)
		{
			if (EngineTypeFilters.Contains(Engine.EngineType))
			{
				Result.Add(Engine);
			}
		}
		// only compare gearbox types
		else if (EngineTypeFilters.Num() == 0 && GearBoxTypeFilters.Num() > 0)
		{
			if (GearBoxTypeFilters.Contains(Engine.GearBoxType))
			{
				Result.Add(Engine);
			}
		}
		// we have some, but not all, of each type of filter, compare both engine types and gearbox types
		else if (EngineTypeFilters.Num() > 0 && EngineTypeFilters.Num() < NumberOfCarEngineTypes && GearBoxTypeFilters.Num() > 0 && GearBoxTypeFilters.Num() < NumberOfCarGearBoxTypes)
		{
			if (EngineTypeFilters.Contains(Engine.EngineType) && GearBoxTypeFilters.Contains(Engine.GearBoxType))
			{
				Result.Add(Engine);
			}
		}
		// we have some, but not all, of the engine types, and all of the gearbox types, compare both engine and gearbox types
		else if (EngineTypeFilters.Num() > 0 && EngineTypeFilters.Num() < NumberOfCarEngineTypes && GearBoxTypeFilters.Num() == NumberOfCarGearBoxTypes)
		{
			if (EngineTypeFilters.Contains(Engine.EngineType) && GearBoxTypeFilters.Contains(Engine.GearBoxType))
			{
				Result.Add(Engine);
			}
		}
		// we have all of the engine types, and some, but not all, of the gearbox types, compare both engine and gearbox types
		else if (EngineTypeFilters.Num() == NumberOfCarEngineTypes && GearBoxTypeFilters.Num() > 0 && GearBoxTypeFilters.Num() < NumberOfCarGearBoxTypes)
		{
			if (EngineTypeFilters.Contains(Engine.EngineType) && GearBoxTypeFilters.Contains(Engine.GearBoxType))
			{
				Result.Add(Engine);
			}
		}
	}

	return Result;
}

bool UCarsData::HasEngineType(const TArray<FCarEngine>& Engines, const ECarEngineType& EngineType) const
{
	bool Result = false;

	if (Engines.Num() > 0)
	{
		for (auto& Engine : Engines)
		{
			if (Engine.EngineType == EngineType)
			{
				Result = true;
				break;
			}
		}
	}

	return Result;
}

bool UCarsData::HasGearBoxType(const TArray<FCarEngine>& Engines, const ECarGearBoxType& GearBoxType) const
{
	bool Result = false;

	if (Engines.Num() > 0)
	{
		for (auto& Engine : Engines)
		{
			if (Engine.GearBoxType == GearBoxType)
			{
				Result = true;
				break;
			}
		}
	}

	return Result;
}


FCarColorExterior UCarsData::GetExteriorColor(const FString& ModelName, const FString& ColorName) const
{
	FCarColorExterior Result;

	const FCarModel Model = GetModel(ModelName);

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
	FCarColorInterior Result;

	const FCarModel Model = GetModel(ModelName);

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
