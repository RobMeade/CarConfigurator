// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ConfiguredCarItemHeading.generated.h"


class UTextBlock;


/**
 * Base class for a configured car item heading, and responsible for binding widgets.
 *	
 * Supports the display of configured car item headings.
 */
UCLASS()
class CARCONFIGURATOR_API UConfiguredCarItemHeading : public UUserWidget
{
	GENERATED_BODY()
	

public:

	/** Used to display the name of the heading */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Name;


protected:


private:

};
