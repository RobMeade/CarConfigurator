// Copyright Rob Meade. All Rights Reserved.


#include "UI/CarConfiguratorHUD.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Engine/Texture2D.h"
#include "Kismet/KismetSystemLibrary.h"

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

		if (CarConfiguratorOverlay->ColorsExterior)
		{
			CarConfiguratorOverlay->ColorsInterior->OnSelectionChanged.AddDynamic(this, &ACarConfiguratorHUD::OnSelectInteriorColor);
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

			UpdateAvailableCars(Cars->GetCars().Num());
			UpdateManufacturers(Cars->GetManufacturers());

			ResetConfiguredCar();
		}
	}
}

void ACarConfiguratorHUD::OnSelectManufacturer(const FString SelectedManufacturer, const ESelectInfo::Type SelectionInfoType) 
{
	if (SelectionInfoType != ESelectInfo::Direct)
	{
		if (Cars)
		{
			SelectManufacturer(Cars->GetManufacturer(SelectedManufacturer));				
		}	
	}
}

void ACarConfiguratorHUD::OnSelectModel(const FString SelectedModel, const ESelectInfo::Type SelectionInfoType)
{
	if (SelectionInfoType != ESelectInfo::Direct)
	{
		if (Cars)
		{
			SelectModel(Cars->GetModel(SelectedModel));			
		}
	}
}

void ACarConfiguratorHUD::OnSelectEngine(const FString SelectedEngine, const ESelectInfo::Type SelectionInfoType)
{
	if (SelectionInfoType != ESelectInfo::Direct)
	{
		if (Cars)
		{
			SelectEngine(Cars->GetEngine(ConfiguredCar.Model.Name, SelectedEngine));
		}
	}
}

void ACarConfiguratorHUD::OnSelectExteriorColor(const FString SelectedExteriorColor, const ESelectInfo::Type SelectionInfoType)
{
	if (SelectionInfoType != ESelectInfo::Direct)
	{
		if (Cars)
		{
			SelectExteriorColor(Cars->GetExteriorColor(ConfiguredCar.Model.Name, SelectedExteriorColor));
		}
	}
}

void ACarConfiguratorHUD::OnSelectInteriorColor(const FString SelectedInteriorColor, const ESelectInfo::Type SelectionInfoType)
{
	if (SelectionInfoType != ESelectInfo::Direct)
	{
		if (Cars)
		{
			SelectInteriorColor(Cars->GetInteriorColor(ConfiguredCar.Model.Name, SelectedInteriorColor));
		}
	}
}

void ACarConfiguratorHUD::UpdateAvailableCars(const int32 AvailableCars) const
{
	if (CarConfiguratorOverlay && CarConfiguratorOverlay->AvailableCars)
	{
		CarConfiguratorOverlay->AvailableCars->SetText(FText::FromString("Available Cars: " + FString::FromInt(AvailableCars)));
	}
}

void ACarConfiguratorHUD::UpdateManufacturers(const TArray<FCarManufacturer>& Manufacturers) const
{
	if (CarConfiguratorOverlay && CarConfiguratorOverlay->Manufacturers)
	{
		CarConfiguratorOverlay->Manufacturers->ClearOptions();

		CarConfiguratorOverlay->Manufacturers->AddOption("Manufacturer");
		CarConfiguratorOverlay->Manufacturers->SetSelectedIndex(0);

		for (auto& Manufacturer : Manufacturers)
		{
			CarConfiguratorOverlay->Manufacturers->AddOption(Manufacturer.Name);
		}		
	}
}

void ACarConfiguratorHUD::UpdateModels(const TArray<FCarModel>& Models) const
{
	if (CarConfiguratorOverlay && CarConfiguratorOverlay->Models)
	{
		ResetModelsAndRelatedOptions();

		CarConfiguratorOverlay->Models->AddOption("Model");
		CarConfiguratorOverlay->Models->SetSelectedIndex(0);

		for (auto& Model : Models)
		{
			CarConfiguratorOverlay->Models->AddOption(Model.Name);
		}		
	}
}

void ACarConfiguratorHUD::UpdateEngines(const TArray<FCarEngine>& Engines) const
{
	if (CarConfiguratorOverlay && CarConfiguratorOverlay->Engines)
	{
		CarConfiguratorOverlay->Engines->ClearOptions();

		CarConfiguratorOverlay->Engines->AddOption("Engine");
		CarConfiguratorOverlay->Engines->SetSelectedIndex(0);

		for (auto& Engine : Engines)
		{
			CarConfiguratorOverlay->Engines->AddOption(Engine.Name);
		}		
	}
}

void ACarConfiguratorHUD::UpdateColorsExterior(const TArray<FCarColorExterior>& ColorsExterior) const
{
	if (CarConfiguratorOverlay && CarConfiguratorOverlay->ColorsExterior)
	{
		CarConfiguratorOverlay->ColorsExterior->ClearOptions();

		CarConfiguratorOverlay->ColorsExterior->AddOption("Color - Exterior");
		CarConfiguratorOverlay->ColorsExterior->SetSelectedIndex(0);

		for (auto& Color : ColorsExterior)
		{
			CarConfiguratorOverlay->ColorsExterior->AddOption(Color.Name);
		}			
	}
}

void ACarConfiguratorHUD::UpdateColorsInterior(const TArray<FCarColorInterior>& ColorsInterior) const
{
	if (CarConfiguratorOverlay && CarConfiguratorOverlay->ColorsExterior)
	{
		CarConfiguratorOverlay->ColorsInterior->ClearOptions();

		CarConfiguratorOverlay->ColorsInterior->AddOption("Color - Interior");
		CarConfiguratorOverlay->ColorsInterior->SetSelectedIndex(0);

		for (auto& Color : ColorsInterior)
		{
			CarConfiguratorOverlay->ColorsInterior->AddOption(Color.Name);
		}
	}
}

void ACarConfiguratorHUD::SelectManufacturer(const FCarManufacturer& Manufacturer)
{
	ResetConfiguredCar();
	ShowModelPreview(false);
	SetConfiguredCarManufacturer(Manufacturer);

	if (Cars)
	{
		UpdateModels(Cars->GetModels(Manufacturer.Name));		
	}	
}

void ACarConfiguratorHUD::SelectModel(const FCarModel& Model) 
{
	FCarModel ConfiguredCarModel = Model;

	if (Model.ExteriorColors.Num() > 0)
	{
		ShowModelPreview(true);
		UpdateModelPreview(Model.ExteriorColors[0].PreviewTexture);		
	}

	// NOTE: We empty Engines, ExteriorColors, and InteriorColors as they will be populated with ALL options for the specified model
	//		 Now that we are creating a ConfiguredCar, we only want the individual selections.
	//		 An alternative approach would be to create a separate data container for the ConfiguredCar.
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

void ACarConfiguratorHUD::ShowModelPreview(const bool bShowModelPreview) const
{
	if (CarConfiguratorOverlay && CarConfiguratorOverlay->ModelPreview)
	{
		const ESlateVisibility Visibility = bShowModelPreview ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
		CarConfiguratorOverlay->ModelPreview->SetVisibility(Visibility);
	}
}

void ACarConfiguratorHUD::UpdateModelPreview(UTexture2D* PreviewTexture) const
{
	if (CarConfiguratorOverlay && CarConfiguratorOverlay->ModelPreview)
	{
		if (PreviewTexture)
		{
			CarConfiguratorOverlay->ModelPreview->SetBrushFromTexture(PreviewTexture);			
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
	const bool bCanUpdateConfiguredCar =
		ConfiguredCarItemClass &&
		ConfiguredCarItemHeadingClass &&
		CarConfiguratorOverlay &&
		CarConfiguratorOverlay->ConfiguredCarOverlay &&
		CarConfiguratorOverlay->ConfiguredCarOverlay->Items &&
		CarConfiguratorOverlay->ConfiguredCarOverlay->TotalPrice;

	if (bCanUpdateConfiguredCar)
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

		// total price
		if (Cars)
		{
			const int32 TotalPrice = Cars->GetTotalPriceForConfiguredCar(ConfiguredCar);
			CarConfiguratorOverlay->ConfiguredCarOverlay->TotalPrice->SetText(GetFormattedPrice(TotalPrice));
		}
	}
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

void ACarConfiguratorHUD::ResetModelsAndRelatedOptions() const
{
	const bool bCanResetCarConfiguratorOverlay = 
		CarConfiguratorOverlay &&
		CarConfiguratorOverlay->Models &&
		CarConfiguratorOverlay->Engines &&
		CarConfiguratorOverlay->ColorsExterior &&
		CarConfiguratorOverlay->ColorsInterior;

	if (bCanResetCarConfiguratorOverlay)
	{
		ResetComboBox(CarConfiguratorOverlay->Models);
		ResetComboBox(CarConfiguratorOverlay->Engines);
		ResetComboBox(CarConfiguratorOverlay->ColorsExterior);
		ResetComboBox(CarConfiguratorOverlay->ColorsInterior);		
	}
}

void ACarConfiguratorHUD::ResetComboBox(UComboBoxString* ComboBox) const
{
	if (ComboBox)
	{
		ComboBox->ClearOptions();		
	}
}

FText ACarConfiguratorHUD::GetFormattedPrice(const int32& Price) const
{
	// NOTE: CurrencyCode is hard-coded, but could be passed in as an ENUM to support other currencies
	return FText::AsCurrencyBase(Price, "GBP");
}

void ACarConfiguratorHUD::OnQuit()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayerController(), EQuitPreference::Quit, true);
}
