// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Widgets/MainMenuWidget.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATIONDUTY_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMainMenuHUD();

protected:
	virtual void BeginPlay() override;
	
private:

	/* ///////////////////////////////////////////////////////
	 *					 Private Properties
	 * //////////////////////////////////////////////////////*/		

	UPROPERTY()
	UMainMenuWidget* ActiveMainMenuWidget;
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	
};
