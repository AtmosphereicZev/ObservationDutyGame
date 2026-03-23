// 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class AODHUD;
enum EAnomalyType : int;
class UAnomalySelectionBox;
class UButton;
class UTextBlock;
class UVerticalBox;
class UImage;
class UOverlay;
class USizeBox;
class UScrollBox;
class UCanvasPanel;
/**
 * 
 */

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnClickedDelegate, UAnomalySelectionBox*, ClickedSelectionBox);

UCLASS()
class OBSERVATIONDUTY_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* ScreenCanvas;
	UPROPERTY(meta=(BindWidget))
	UButton* PreviousCameraButton;
	UPROPERTY(meta=(BindWidget))
	UButton* NextCameraButton;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NC_TXT;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PC_TXT;
	
	// Report Anomalies Box
	UPROPERTY(meta=(BindWidget))
	USizeBox* ReportAnomalyBox;
	UPROPERTY(meta=(BindWidget))
	UOverlay* RA_MainOverlay;
	UPROPERTY(meta=(BindWidget))
	UImage* RA_Background;
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* RA_VB;
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* RA_TopVerticalBox;
	UPROPERTY(meta=(BindWidget))
	UOverlay* RA_TopOverlay;
	UPROPERTY(meta=(BindWidget))
	UImage* RA_TextBackground;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* RA_TopText;
	UPROPERTY(meta=(BindWidget))
	UScrollBox* RA_SB;
	UPROPERTY(meta=(BindWidget))
	UButton* RA_ReportButton;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* RA_ButtonText;

	/* ///////////////////////////////////////////////////////
	 *						  Properties
	 * //////////////////////////////////////////////////////*/	

	UPROPERTY()
	TSubclassOf<UUserWidget> AnomalySelectionBoxClass;
	UPROPERTY()
	AODHUD* HUD;

	/* ///////////////////////////////////////////////////////
	 *						  Functions
	 * //////////////////////////////////////////////////////*/	

	UFUNCTION()
	virtual void NativeConstruct() override;
	UFUNCTION()
	void SetupWidget();
	UFUNCTION()
	void OnSelectionBoxClicked(UAnomalySelectionBox* BoxClicked);
	UFUNCTION()
	void OnReportButtonClicked();
	UFUNCTION()
	void ReportAnomaly(EAnomalyType AnomalyType);
	UFUNCTION()
	void UnselectAnomalySelection(APawn* OldPawn, APawn* NewPawn);
	
protected:

	UFUNCTION()
	void OnNextCameraClicked();
	UFUNCTION()
	void OnPreviousCameraClicked();
	
private:

	UPROPERTY()
	UAnomalySelectionBox* CurrentlySelectedBox;
	
};
