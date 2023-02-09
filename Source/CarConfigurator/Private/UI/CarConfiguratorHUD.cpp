// Copyright Rob Meade. All Rights Reserved.


#include "UI/CarConfiguratorHUD.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Engine/Texture2D.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Misc/Paths.h"

#include "Types/CarEngine.h"
#include "Types/CarManufacturer.h"
#include "Types/CarModel.h"
#include "UI/CarConfiguratorOverlay.h"
#include "UI/ConfiguredCarItem.h"
#include "UI/ConfiguredCarItemHeading.h"
#include "UI/ConfiguredCarOverlay.h"


void ACarConfiguratorHUD::BeginPlay()
{
	Super::BeginPlay();

	AddCarConfiguratorOverlay();
	BindDelegates();
}

void ACarConfiguratorHUD::AddCarConfiguratorOverlay()
{
	if (GetOwningPlayerController() && CarConfiguratorOverlayClass)
	{
		CarConfiguratorOverlay = CreateWidget<UCarConfiguratorOverlay>(GetOwningPlayerController(), CarConfiguratorOverlayClass);
		CarConfiguratorOverlay->AddToViewport();
	}
}

void ACarConfiguratorHUD::BindDelegates()
{
	if (CarConfiguratorOverlay)
	{
		if (CarConfiguratorOverlay->Manufacturers)
		{
			CarConfiguratorOverlay->Manufacturers->OnSelectionChanged.AddDynamic(this, &ACarConfiguratorHUD::OnSelectManufacturer);
		}

		if (CarConfiguratorOverlay->Models)
		{
			CarConfiguratorOverlay->Models->OnSelectionChanged.AddDynamic(this, &ACarConfiguratorHUD::OnSelectModel);
		}

		if (CarConfiguratorOverlay->Engines)
		{
			CarConfiguratorOverlay->Engines->OnSelectionChanged.AddDynamic(this, &ACarConfiguratorHUD::OnSelectEngine);
		}

		if (CarConfiguratorOverlay->ColorsExterior)
		{
			CarConfiguratorOverlay->ColorsExterior->OnSelectionChanged.AddDynamic(this, &ACarConfiguratorHUD::OnSelectExteriorColor);
		}

		if (CarConfiguratorOverlay->ColorsInterior)
		{
			CarConfiguratorOverlay->ColorsInterior->OnSelectionChanged.AddDynamic(this, &ACarConfiguratorHUD::OnSelectInteriorColor);
		}

		if (CarConfiguratorOverlay->FuelFilterPetrol)
		{
			CarConfiguratorOverlay->FuelFilterPetrol->OnCheckStateChanged.AddDynamic(this, &ACarConfiguratorHUD::OnFuelFilterPetrolCheckStateChanged);
		}

		if (CarConfiguratorOverlay->FuelFilterDiesel)
		{
			CarConfiguratorOverlay->FuelFilterDiesel->OnCheckStateChanged.AddDynamic(this, &ACarConfiguratorHUD::OnFuelFilterDieselCheckStateChanged);
		}

		if (CarConfiguratorOverlay->FuelFilterElectric)
		{
			CarConfiguratorOverlay->FuelFilterElectric->OnCheckStateChanged.AddDynamic(this, &ACarConfiguratorHUD::OnFuelFilterElectricCheckStateChanged);
		}

		if (CarConfiguratorOverlay->FuelFilterHybrid)
		{
			CarConfiguratorOverlay->FuelFilterHybrid->OnCheckStateChanged.AddDynamic(this, &ACarConfiguratorHUD::OnFuelFilterHybridCheckStateChanged);
		}

		if (CarConfiguratorOverlay->GearboxFilterManual)
		{
			CarConfiguratorOverlay->GearboxFilterManual->OnCheckStateChanged.AddDynamic(this, &ACarConfiguratorHUD::OnGearBoxFilterManualCheckStateChanged);
		}

		if (CarConfiguratorOverlay->GearboxFilterAutomatic)
		{
			CarConfiguratorOverlay->GearboxFilterAutomatic->OnCheckStateChanged.AddDynamic(this, &ACarConfiguratorHUD::OnGearBoxFilterAutomaticCheckStateChanged);
		}

		if (CarConfiguratorOverlay->ScreenShot)
		{
			CarConfiguratorOverlay->ScreenShot->OnClicked.AddDynamic(this, &ACarConfiguratorHUD::TakeScreenShot);
		}

		if (CarConfiguratorOverlay->Quit)
		{
			CarConfiguratorOverlay->Quit->OnClicked.AddDynamic(this, &ACarConfiguratorHUD::OnQuit);
		}
	}
}

void ACarConfiguratorHUD::DisplayCarData()
{
	if (CarConfiguratorOverlay && CarsData)
	{
		Cars = CarsData.GetDefaultObject();

		if (Cars)
		{
			Cars->InitializeData();

			UpdateAvailableCars(Cars->GetCars().Num(), Cars->GetManufacturers().Num());
			UpdateManufacturers(Cars->GetManufacturers());
		}
	}
}

void ACarConfiguratorHUD::OnSelectManufacturer(const FString SelectedManufacturer, const ESelectInfo::Type SelectionInfoType) 
{
	const bool bCanSelectManufacturer =
		Cars &&
		CarConfiguratorOverlay &&
		CarConfiguratorOverlay->Manufacturers &&
		CarConfiguratorOverlay->Manufacturers->GetIsEnabled();

	if (bCanSelectManufacturer)
	{
		SelectManufacturer(Cars->GetManufacturer(SelectedManufacturer));				
	}	
}

void ACarConfiguratorHUD::OnSelectModel(const FString SelectedModel, const ESelectInfo::Type SelectionInfoType)
{
	const bool bCanSelectModel =
		Cars &&
		CarConfiguratorOverlay &&
		CarConfiguratorOverlay->Models &&
		CarConfiguratorOverlay->Models->GetIsEnabled();

	if (bCanSelectModel)
	{
		SelectModel(Cars->GetModel(SelectedModel));			
	}
}

void ACarConfiguratorHUD::OnSelectEngine(const FString SelectedEngine, const ESelectInfo::Type SelectionInfoType)
{
	const bool bCanSelectEngine =
		Cars &&
		CarConfiguratorOverlay &&
		CarConfiguratorOverlay->Engines &&
		CarConfiguratorOverlay->Engines->GetIsEnabled();

	if (bCanSelectEngine)
	{
		SelectEngine(Cars->GetEngine(ConfiguredCar.Model.Name, SelectedEngine));
	}
}

void ACarConfiguratorHUD::OnSelectExteriorColor(const FString SelectedExteriorColor, const ESelectInfo::Type SelectionInfoType)
{
	const bool bCanSelectExteriorColor =
		Cars &&
		CarConfiguratorOverlay &&
		CarConfiguratorOverlay->ColorsExterior &&
		CarConfiguratorOverlay->ColorsExterior->GetIsEnabled();

	if (bCanSelectExteriorColor)
	{
		SelectExteriorColor(Cars->GetExteriorColor(ConfiguredCar.Model.Name, SelectedExteriorColor));
	}
}

void ACarConfiguratorHUD::OnSelectInteriorColor(const FString SelectedInteriorColor, const ESelectInfo::Type SelectionInfoType)
{
	const bool bCanSelectInteriorColor =
		Cars &&
		CarConfiguratorOverlay &&
		CarConfiguratorOverlay->ColorsInterior &&
		CarConfiguratorOverlay->ColorsInterior->GetIsEnabled();

	if (bCanSelectInteriorColor)
	{
		SelectInteriorColor(Cars->GetInteriorColor(ConfiguredCar.Model.Name, SelectedInteriorColor));			
	}
}

void ACarConfiguratorHUD::OnFuelFilterPetrolCheckStateChanged(bool bIsChecked)
{
	if (bIsChecked)
	{
		EngineTypeFilters.AddUnique(ECarEngineType::ECET_Petrol);
	}
	else
	{
		EngineTypeFilters.Remove(ECarEngineType::ECET_Petrol);
	}

	if (Cars)
	{
		UpdateEngines(Cars->GetEnginesFiltered(ConfiguredCar.Model.Name, EngineTypeFilters, GearBoxTypeFilters));	
	}
}

void ACarConfiguratorHUD::OnFuelFilterDieselCheckStateChanged(bool bIsChecked)
{
	if (bIsChecked)
	{
		EngineTypeFilters.AddUnique(ECarEngineType::ECET_Diesel);
	}
	else
	{
		EngineTypeFilters.Remove(ECarEngineType::ECET_Diesel);
	}

	UpdateEngines(Cars->GetEnginesFiltered(ConfiguredCar.Model.Name, EngineTypeFilters, GearBoxTypeFilters));
}

void ACarConfiguratorHUD::OnFuelFilterElectricCheckStateChanged(bool bIsChecked)
{
	if (bIsChecked)
	{
		EngineTypeFilters.AddUnique(ECarEngineType::ECET_Electric);
	}
	else
	{
		EngineTypeFilters.Remove(ECarEngineType::ECET_Electric);
	}

	UpdateEngines(Cars->GetEnginesFiltered(ConfiguredCar.Model.Name, EngineTypeFilters, GearBoxTypeFilters));
}

void ACarConfiguratorHUD::OnFuelFilterHybridCheckStateChanged(bool bIsChecked)
{
	if (bIsChecked)
	{
		EngineTypeFilters.AddUnique(ECarEngineType::ECET_Hybrid);
	}
	else
	{
		EngineTypeFilters.Remove(ECarEngineType::ECET_Hybrid);
	}

	UpdateEngines(Cars->GetEnginesFiltered(ConfiguredCar.Model.Name, EngineTypeFilters, GearBoxTypeFilters));
}

void ACarConfiguratorHUD::OnGearBoxFilterManualCheckStateChanged(bool bIsChecked)
{
	if (bIsChecked)
	{
		GearBoxTypeFilters.AddUnique(ECarGearBoxType::ECGT_Manual);
	}
	else
	{
		GearBoxTypeFilters.Remove(ECarGearBoxType::ECGT_Manual);
	}

	UpdateEngines(Cars->GetEnginesFiltered(ConfiguredCar.Model.Name, EngineTypeFilters, GearBoxTypeFilters));
}

void ACarConfiguratorHUD::OnGearBoxFilterAutomaticCheckStateChanged(bool bIsChecked)
{
	if (bIsChecked)
	{
		GearBoxTypeFilters.AddUnique(ECarGearBoxType::ECGT_Automatic);
	}
	else
	{
		GearBoxTypeFilters.Remove(ECarGearBoxType::ECGT_Automatic);
	}
	
	UpdateEngines(Cars->GetEnginesFiltered(ConfiguredCar.Model.Name, EngineTypeFilters, GearBoxTypeFilters));
}

void ACarConfiguratorHUD::UpdateAvailableCars(const int32 AvailableCars, const int32 UniqueManufacturers) const
{
	if (CarConfiguratorOverlay && CarConfiguratorOverlay->AvailableCars)
	{
		const FString AvailableCarsText = 
			FString::FromInt(AvailableCars) + " (" + 
			FString::FromInt(AvailableCars) + " models, " + 
			FString::FromInt(UniqueManufacturers) + " manufacturers)";

		CarConfiguratorOverlay->AvailableCars->SetText(FText::FromString(AvailableCarsText));
	}
}

void ACarConfiguratorHUD::UpdateManufacturers(const TArray<FCarManufacturer>& Manufacturers) const
{
	if (CarConfiguratorOverlay && CarConfiguratorOverlay->Manufacturers)
	{
		AddComboBoxOptions<FCarManufacturer>(CarConfiguratorOverlay->Manufacturers, Manufacturers);
	}
}

void ACarConfiguratorHUD::UpdateModels(const TArray<FCarModel>& Models) const
{
	if (CarConfiguratorOverlay && CarConfiguratorOverlay->Models)
	{
		AddComboBoxOptions<FCarModel>(CarConfiguratorOverlay->Models, Models);
	}
}

void ACarConfiguratorHUD::UpdateEngines(const TArray<FCarEngine>& Engines)
{
	if (CarConfiguratorOverlay && CarConfiguratorOverlay->Engines)
	{
		AddComboBoxOptions<FCarEngine>(CarConfiguratorOverlay->Engines, Engines);
	}

	UpdateEngineFilteringOptions(Engines);
}

void ACarConfiguratorHUD::UpdateColorsExterior(const TArray<FCarColorExterior>& ColorsExterior) const
{
	if (CarConfiguratorOverlay && CarConfiguratorOverlay->ColorsExterior)
	{
		AddComboBoxOptions<FCarColorExterior>(CarConfiguratorOverlay->ColorsExterior, ColorsExterior);
	}
}

void ACarConfiguratorHUD::UpdateColorsInterior(const TArray<FCarColorInterior>& ColorsInterior) const
{
	if (CarConfiguratorOverlay && CarConfiguratorOverlay->ColorsExterior)
	{
		AddComboBoxOptions<FCarColorInterior>(CarConfiguratorOverlay->ColorsInterior, ColorsInterior);
	}
}

void ACarConfiguratorHUD::SelectManufacturer(const FCarManufacturer& Manufacturer)
{
	ResetEngineFiltering();
	ReInitializeCarConfigurator(false);
	SetConfiguredCarManufacturer(Manufacturer);

	if (Cars)
	{
		UpdateModels(Cars->GetModels(Manufacturer.Name));		
	}	
}

void ACarConfiguratorHUD::SelectModel(const FCarModel& Model) 
{
	ReInitializeCarConfigurator(true);
	ResetEngineFiltering();

	FCarModel ConfiguredCarModel = Model;
	
	// NOTE: We empty Engines, ExteriorColors, and InteriorColors as they will be populated with ALL options for the specified model
	// Now that we are creating a ConfiguredCar, we only want the individual selections.
	// An alternative approach would be to create a separate data container for the ConfiguredCar.

	ConfiguredCarModel.Engines.Empty();
	ConfiguredCarModel.ExteriorColors.Empty();
	ConfiguredCarModel.InteriorColors.Empty();

	SetConfiguredCarModel(ConfiguredCarModel);

	UpdateEngines(Model.Engines);
	UpdateColorsExterior(Model.ExteriorColors);
	UpdateColorsInterior(Model.InteriorColors);
}

void ACarConfiguratorHUD::SelectEngine(const FCarEngine& Engine)
{
	SetConfiguredCarEngine(Engine);
}

void ACarConfiguratorHUD::SelectExteriorColor(const FCarColorExterior& ExteriorColor)
{
	SetConfiguredCarExteriorColor(ExteriorColor);

	UpdateModelPreview(ExteriorColor.PreviewTexture);
}

void ACarConfiguratorHUD::SelectInteriorColor(const FCarColorInterior& InteriorColor)
{
	SetConfiguredCarInteriorColor(InteriorColor);
}

void ACarConfiguratorHUD::UpdateModelPreview(UTexture2D* PreviewTexture) const
{
	if (CarConfiguratorOverlay && CarConfiguratorOverlay->ModelPreview)
	{
		if (PreviewTexture)
		{
			CarConfiguratorOverlay->ModelPreview->SetVisibility(ESlateVisibility::Visible);				
			CarConfiguratorOverlay->ModelPreview->SetBrushFromTexture(PreviewTexture);			
		}
		else
		{
			CarConfiguratorOverlay->ModelPreview->SetVisibility(ESlateVisibility::Hidden);
			CarConfiguratorOverlay->ModelPreview->SetBrushFromTexture(nullptr);
		}
	}
}

void ACarConfiguratorHUD::SetConfiguredCarManufacturer(const FCarManufacturer& ManufacturerToConfigure)
{
	ConfiguredCar.Manufacturer = ManufacturerToConfigure;
}

void ACarConfiguratorHUD::SetConfiguredCarModel(const FCarModel& ModelToConfigure)
{
	ConfiguredCar.Model = ModelToConfigure;
	UpdateConfiguredCar();
}

void ACarConfiguratorHUD::SetConfiguredCarEngine(const FCarEngine& EngineToConfigure)
{
	ConfiguredCar.Model.Engines.Empty();
	ConfiguredCar.Model.Engines.Add(EngineToConfigure);
	UpdateConfiguredCar();
}

void ACarConfiguratorHUD::SetConfiguredCarExteriorColor(const FCarColorExterior& ColorExteriorToConfigure)
{
	ConfiguredCar.Model.ExteriorColors.Empty();
	ConfiguredCar.Model.ExteriorColors.Add(ColorExteriorToConfigure);
	UpdateConfiguredCar();
}

void ACarConfiguratorHUD::SetConfiguredCarInteriorColor(const FCarColorInterior& ColorInteriorToConfigure)
{
	ConfiguredCar.Model.InteriorColors.Empty();
	ConfiguredCar.Model.InteriorColors.Add(ColorInteriorToConfigure);
	UpdateConfiguredCar();
}

void ACarConfiguratorHUD::UpdateConfiguredCar()
{
	// reset
	ResetConfiguredCar();

	// manufacturer
	AddConfiguredCarItemHeading("Manufacturer");
	AddConfiguredCarItem(ConfiguredCar.Manufacturer.Name);

	// model
	AddConfiguredCarItemHeading("Model");
	AddConfiguredCarItem(ConfiguredCar.Model.Name, ConfiguredCar.Model.Description, ConfiguredCar.Model.BasePrice);

	// engine
	if (ConfiguredCar.Model.Engines.Num() > 0)
	{
		AddConfiguredCarItemHeading("Engine");
		AddConfiguredCarItem(ConfiguredCar.Model.Engines[0].Name, ConfiguredCar.Model.Engines[0].Description, ConfiguredCar.Model.Engines[0].Price);
	}

	// color - exterior
	if (ConfiguredCar.Model.ExteriorColors.Num() > 0)
	{
		AddConfiguredCarItemHeading("Color - Exterior");
		AddConfiguredCarItem(ConfiguredCar.Model.ExteriorColors[0].Name, ConfiguredCar.Model.ExteriorColors[0].Price);			
	}

	// color - interior
	if (ConfiguredCar.Model.InteriorColors.Num() > 0)
	{
		AddConfiguredCarItemHeading("Color - Interior");
		AddConfiguredCarItem(ConfiguredCar.Model.InteriorColors[0].Name, ConfiguredCar.Model.InteriorColors[0].Price);			
	}

	UpdateTotalPrice();
}

void ACarConfiguratorHUD::AddConfiguredCarItemHeading(const FString Name) const
{
	const bool bCanAddConfiguredCarItemHeading =
		GetOwningPlayerController() &&
		ConfiguredCarItemHeadingClass &&
		CarConfiguratorOverlay &&
		CarConfiguratorOverlay->ConfiguredCarOverlay &&
		CarConfiguratorOverlay->ConfiguredCarOverlay->Items;

	if (bCanAddConfiguredCarItemHeading)
	{
		UConfiguredCarItemHeading* ConfiguredItemHeading = CreateWidget<UConfiguredCarItemHeading>(GetOwningPlayerController(), ConfiguredCarItemHeadingClass);

		if (ConfiguredItemHeading && ConfiguredItemHeading->Name)
		{
			ConfiguredItemHeading->Name->SetText(FText::FromString(Name));
			CarConfiguratorOverlay->ConfiguredCarOverlay->Items->AddChildToVerticalBox(ConfiguredItemHeading);			
		}
	}
}

void ACarConfiguratorHUD::AddConfiguredCarItem(const FString& Name, const FString& Description, const int32& Price) const
{
	const bool bCanAddConfiguredCarItem = 
		GetOwningPlayerController() &&
		ConfiguredCarItemClass &&
		CarConfiguratorOverlay &&
		CarConfiguratorOverlay->ConfiguredCarOverlay &&
		CarConfiguratorOverlay->ConfiguredCarOverlay->Items;

	if (bCanAddConfiguredCarItem)
	{
		UConfiguredCarItem* ConfiguredItem = CreateWidget<UConfiguredCarItem>(GetOwningPlayerController(), ConfiguredCarItemClass);

		if (ConfiguredItem && ConfiguredItem->Name && ConfiguredItem->Description && ConfiguredItem->Price)
		{
			ConfiguredItem->Name->SetText(FText::FromString(Name));

			if (Description != "")
			{
				ConfiguredItem->Description->SetText(FText::FromString(Description));				
			}

			if (Price >= 0)
			{
				ConfiguredItem->Price->SetText(GetFormattedPrice(Price));				
			}

			CarConfiguratorOverlay->ConfiguredCarOverlay->Items->AddChildToVerticalBox(ConfiguredItem);
		}
	}
}

void ACarConfiguratorHUD::AddConfiguredCarItem(const FString& Name, const int32& Price) const
{
	AddConfiguredCarItem(Name, "", Price);
}

void ACarConfiguratorHUD::AddConfiguredCarItem(const FString& Name) const
{
	AddConfiguredCarItem(Name, "", -1);
}

void ACarConfiguratorHUD::UpdateTotalPrice() const
{
	const bool bCanUpdateTotalPrice =
		Cars &&
		CarConfiguratorOverlay &&
		CarConfiguratorOverlay->ConfiguredCarOverlay &&
		CarConfiguratorOverlay->ConfiguredCarOverlay->TotalPrice;

	if (bCanUpdateTotalPrice)
	{
		const int32 TotalPrice = Cars->GetTotalPriceForConfiguredCar(ConfiguredCar);
		CarConfiguratorOverlay->ConfiguredCarOverlay->TotalPrice->SetText(GetFormattedPrice(TotalPrice));		
	}
}

void ACarConfiguratorHUD::ResetConfiguredCar() const
{
	const bool bCanResetConfiguredCar =
		CarConfiguratorOverlay &&
		CarConfiguratorOverlay->ConfiguredCarOverlay &&
		CarConfiguratorOverlay->ConfiguredCarOverlay->Items &&
		CarConfiguratorOverlay->ConfiguredCarOverlay->TotalPrice;

	if (bCanResetConfiguredCar)
	{
		CarConfiguratorOverlay->ConfiguredCarOverlay->Items->ClearChildren();
		CarConfiguratorOverlay->ConfiguredCarOverlay->TotalPrice->SetText(GetFormattedPrice(0));		
	}
}

void ACarConfiguratorHUD::UpdateEngineFilteringOptions(const TArray<FCarEngine>& Engines)
{
	if (Cars && Engines.Num() > 0)
	{
		// engine type filters
		EnableEngineTypeFilter(ECarEngineType::ECET_Petrol, Cars->HasEngineType(Engines, ECarEngineType::ECET_Petrol));
		EnableEngineTypeFilter(ECarEngineType::ECET_Diesel, Cars->HasEngineType(Engines, ECarEngineType::ECET_Diesel));
		EnableEngineTypeFilter(ECarEngineType::ECET_Electric, Cars->HasEngineType(Engines, ECarEngineType::ECET_Electric));
		EnableEngineTypeFilter(ECarEngineType::ECET_Hybrid, Cars->HasEngineType(Engines, ECarEngineType::ECET_Hybrid));

		// gearbox type filters
		EnableGearBoxTypeFilter(ECarGearBoxType::ECGT_Manual, Cars->HasGearBoxType(Engines, ECarGearBoxType::ECGT_Manual));
		EnableGearBoxTypeFilter(ECarGearBoxType::ECGT_Automatic, Cars->HasGearBoxType(Engines, ECarGearBoxType::ECGT_Automatic));
	}
	else
	{
		DisableAllEngineFilters();
	}
}

void ACarConfiguratorHUD::ResetEngineFiltering()
{
	if (CarConfiguratorOverlay)
	{
		SetCheckBoxCheckedState(CarConfiguratorOverlay->FuelFilterPetrol, ECheckBoxState::Unchecked);
		SetCheckBoxCheckedState(CarConfiguratorOverlay->FuelFilterDiesel, ECheckBoxState::Unchecked);
		SetCheckBoxCheckedState(CarConfiguratorOverlay->FuelFilterElectric, ECheckBoxState::Unchecked);
		SetCheckBoxCheckedState(CarConfiguratorOverlay->FuelFilterHybrid, ECheckBoxState::Unchecked);	
		SetCheckBoxCheckedState(CarConfiguratorOverlay->GearboxFilterManual, ECheckBoxState::Unchecked);	
		SetCheckBoxCheckedState(CarConfiguratorOverlay->GearboxFilterAutomatic, ECheckBoxState::Unchecked);		
	}

	EngineTypeFilters.Empty();
	GearBoxTypeFilters.Empty();
}

void ACarConfiguratorHUD::EnableEngineTypeFilter(const ECarEngineType& EngineType, const bool bIsEnabled)
{
	if (CarConfiguratorOverlay)
	{
		switch (EngineType)
		{
		case ECarEngineType::ECET_Petrol:
			EnableCheckBox(CarConfiguratorOverlay->FuelFilterPetrol, bIsEnabled);
			break;

		case ECarEngineType::ECET_Diesel:
			EnableCheckBox(CarConfiguratorOverlay->FuelFilterDiesel, bIsEnabled);
			break;

		case ECarEngineType::ECET_Electric:
			EnableCheckBox(CarConfiguratorOverlay->FuelFilterElectric, bIsEnabled);
			break;

		case ECarEngineType::ECET_Hybrid:
			EnableCheckBox(CarConfiguratorOverlay->FuelFilterHybrid, bIsEnabled);
			break;

		default:
			break;
		}		
	}
}

void ACarConfiguratorHUD::EnableGearBoxTypeFilter(const ECarGearBoxType& GearBoxType, const bool bIsEnabled)
{
	if (CarConfiguratorOverlay)
	{
		switch (GearBoxType)
		{
		case ECarGearBoxType::ECGT_Manual:
			EnableCheckBox(CarConfiguratorOverlay->GearboxFilterManual, bIsEnabled);
			break;

		case ECarGearBoxType::ECGT_Automatic:
			EnableCheckBox(CarConfiguratorOverlay->GearboxFilterAutomatic, bIsEnabled);
			break;

		default:
			break;
		}
	}
}

void ACarConfiguratorHUD::EnableAllEngineFilters()
{
	if (CarConfiguratorOverlay)
	{
		EnableCheckBox(CarConfiguratorOverlay->FuelFilterPetrol, true);
		EnableCheckBox(CarConfiguratorOverlay->FuelFilterDiesel, true);
		EnableCheckBox(CarConfiguratorOverlay->FuelFilterElectric, true);
		EnableCheckBox(CarConfiguratorOverlay->FuelFilterHybrid, true);	
		EnableCheckBox(CarConfiguratorOverlay->GearboxFilterManual, true);	
		EnableCheckBox(CarConfiguratorOverlay->GearboxFilterAutomatic, true);	
	}
}

void ACarConfiguratorHUD::DisableAllEngineFilters()
{
	if (CarConfiguratorOverlay)
	{
		EnableCheckBox(CarConfiguratorOverlay->FuelFilterPetrol, false);
		EnableCheckBox(CarConfiguratorOverlay->FuelFilterDiesel, false);
		EnableCheckBox(CarConfiguratorOverlay->FuelFilterElectric, false);
		EnableCheckBox(CarConfiguratorOverlay->FuelFilterHybrid, false);	
		EnableCheckBox(CarConfiguratorOverlay->GearboxFilterManual, false);	
		EnableCheckBox(CarConfiguratorOverlay->GearboxFilterAutomatic, false);	
	}
}

template<typename T>
void ACarConfiguratorHUD::AddComboBoxOptions(UComboBoxString* ComboBox, const TArray<T>& Options) const
{
	if (ComboBox)
	{
		// disable combobox as ClearOptions() will trigger OnSelectionChanged() to be called
		ComboBox->SetIsEnabled(false);
		ComboBox->ClearOptions();

		if (Options.Num() > 0)
		{
			for (T Option : Options)
			{
				ComboBox->AddOption(Option.Name);
			}

			ComboBox->SetIsEnabled(true);
		}
		else
		{	
			ComboBox->AddOption("None Available");
		}

		// must be called after SetIsEnabled()
		// if not, OnSelectionChanged delegates will not handle the selection
		ComboBox->SetSelectedIndex(0);
	}
}

void ACarConfiguratorHUD::ResetComboBox(UComboBoxString* ComboBox) const
{
	if (ComboBox)
	{
		ComboBox->ClearOptions();		
	}
}

void ACarConfiguratorHUD::SetCheckBoxCheckedState(UCheckBox* CheckBox, const ECheckBoxState& CheckBoxState) const
{
	if (CheckBox)
	{
		// setting the checkbox to disabled before changing it's state prevents a response to OnCheckedStateChanged 
		CheckBox->SetIsEnabled(false);
		CheckBox->SetCheckedState(CheckBoxState);
		CheckBox->SetIsEnabled(true);
	}
}

void ACarConfiguratorHUD::EnableCheckBox(UCheckBox* CheckBox, const bool bIsEnabled)
{
	if (CheckBox)
	{
		CheckBox->SetIsEnabled(bIsEnabled);
	}
}

FText ACarConfiguratorHUD::GetFormattedPrice(const int32& Price) const
{
	// NOTE: CurrencyCode is hard-coded, but could be passed in as an ENUM to support other currencies
	return FText::AsCurrencyBase(Price, "GBP");
}

void ACarConfiguratorHUD::ReInitializeCarConfigurator(const bool bRetainManufacturer)
{
	// retaining the manufacturer is necessary in the scenario of a different model being chosen for the same manufacturer
	// failure to do so will mean that the manufacturer data is lost, and not displayed on the configured car overlay
	if (bRetainManufacturer)
	{
		FCarManufacturer Manufacturer = ConfiguredCar.Manufacturer;

		ConfiguredCar = FCar();
		ConfiguredCar.Manufacturer = Manufacturer;
	}
	else
	{
		// reset the data container
		ConfiguredCar = FCar();		
	}

	ResetConfiguredCar();	
}

void ACarConfiguratorHUD::TakeScreenShot()
{
	FScreenshotRequest::RequestScreenshot("ScreenShot", true, true);

	const FString ScreenShotDirectory = FPaths::ConvertRelativePathToFull(FPaths::ScreenShotDir());
	UKismetSystemLibrary::LaunchURL("file://" + ScreenShotDirectory);
}

void ACarConfiguratorHUD::OnQuit()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayerController(), EQuitPreference::Quit, true);
}
