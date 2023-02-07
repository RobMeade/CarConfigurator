// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ConfiguredCarOverlay.generated.h"


class UTextBlock;
class UVerticalBox;


/**
 *	Base class for the configured car overlay and responsible for binding widgets.
 *
 *	Supports the display of configured car information related to the players choices and the total cost of those choices.
 */
UCLASS()
class CARCONFIGURATOR_API UConfiguredCarOverlay : public UUserWidget
{
	GENERATED_BODY()


public:

	/**
	 *	Used as a container to display configured car items
	 */
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* Items;

	/**
	 *	Used to display the total price of the configured items
	 */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TotalPrice;


protected:


private:


	
};
