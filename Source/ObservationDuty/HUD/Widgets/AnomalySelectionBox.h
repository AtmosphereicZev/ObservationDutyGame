// 

#pragma once

#include "CoreMinimal.h"
#include "MainWidget.h"
#include "Blueprint/UserWidget.h"
#include "AnomalySelectionBox.generated.h"

enum EAnomalyType : int;
class UTextBlock;
class UCanvasPanel;
/**
 * 
 */

UCLASS()
class OBSERVATIONDUTY_API UAnomalySelectionBox : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* Canvas;
	UPROPERTY(meta=(BindWidget))
	UButton* Button;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ButtonText;

	/* ///////////////////////////////////////////////////////
	 *					 Public Functions
	 * //////////////////////////////////////////////////////*/			

	virtual void NativeConstruct() override;
	void SetupSelectionBox(const FString AnomalyName, EAnomalyType SelectionType);
	EAnomalyType GetSelectionType() const {return m_SelectionType;}

	void HighlightBox();
	void UnhighlightBox();
	
	// Events
	FOnClickedDelegate OnClickedDelegate;
	
protected:

	/* ///////////////////////////////////////////////////////
	 *					 Protected Functions
	 * //////////////////////////////////////////////////////*/			

	UFUNCTION()
	void OnButtonClicked();
	
	/* ///////////////////////////////////////////////////////
	 *					Protected Properties
	 * //////////////////////////////////////////////////////*/			

	EAnomalyType m_SelectionType;
	
};
