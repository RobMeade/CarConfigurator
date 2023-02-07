// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ConfiguredCarItem.generated.h"


class UTextBlock;


/**
 * Base class for a configured car item and responsible for binding widgets.
 *
 * Supports the display of configured car items.
 */
UCLASS()
class CARCONFIGURATOR_API UConfiguredCarItem : public UUserWidget
{
	GENERATED_BODY()


public:

	/** Used to display the name of the configured car item */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Name;

	/** Used to display the price of the configured car item */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Price;

	/** Used to display the description of the configured car item */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Description;


protected:


private:


};
