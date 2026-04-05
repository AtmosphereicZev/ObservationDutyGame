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

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* MainCanvas;
	
};
