// 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UCanvasPanel;
/**
 * 
 */
UCLASS()
class OBSERVATIONDUTY_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	/**
	 * Most basically all the Main Menu widget is in the widget blueprint. :)
	 */
	
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* MainCanvas;

	/* ///////////////////////////////////////////////////////
	 *						  Animations
	 * //////////////////////////////////////////////////////*/	

	UPROPERTY(Transient, meta=(BindWidgetAnim), BlueprintReadWrite)
	UWidgetAnimation* StartAnimation;
	UPROPERTY(Transient, meta=(BindWidgetAnim), BlueprintReadWrite)
	UWidgetAnimation* TransitionAnimation;

	
};
