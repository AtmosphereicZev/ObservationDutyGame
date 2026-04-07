// 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class UWidgetSwitcher;
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
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CameraName;
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite)
	UWidgetSwitcher* UISwitcher;
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite)
	UButton* B_Play;
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite)
	UButton* B_Menu;

	
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
	 *						  Animations
	 * //////////////////////////////////////////////////////*/	

	UPROPERTY(Transient, meta=(BindWidgetAnim), BlueprintReadWrite)
	UWidgetAnimation* LoadAnimation;
	UPROPERTY(Transient, meta=(BindWidgetAnim), BlueprintReadWrite)
	UWidgetAnimation* PauseAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim), BlueprintReadWrite)
	UWidgetAnimation* SwitchAnimation;
	UPROPERTY(Transient, meta=(BindWidgetAnim), BlueprintReadWrite)
	UWidgetAnimation* ReturnAnimation;
	
	/* ///////////////////////////////////////////////////////
	 *						  Properties
	 * //////////////////////////////////////////////////////*/	

	UPROPERTY()
	TSubclassOf<UUserWidget> AnomalySelectionBoxClass;
	UPROPERTY()
	AODHUD* HUD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAllowUISwitch = true;
	
	/* ///////////////////////////////////////////////////////
	 *						  Functions
	 * //////////////////////////////////////////////////////*/	

	UFUNCTION()
	virtual void NativeConstruct() override;
	UFUNCTION()
	void SetupWidget();
	UFUNCTION()
	void SetCameraText(FString Name);
	UFUNCTION()
	void OnSelectionBoxClicked(UAnomalySelectionBox* BoxClicked);
	UFUNCTION()
	void OnReportButtonClicked();
	UFUNCTION()
	void ReportAnomaly(EAnomalyType AnomalyType);
	UFUNCTION()
	void OnCameraChanged(APawn* OldPawn, APawn* NewPawn);
	UFUNCTION()
	void ChangeToPaused(bool bPaused);
	
protected:

	UFUNCTION()
	void OnNextCameraClicked();
	UFUNCTION()
	void OnPreviousCameraClicked();
	UFUNCTION()
	void OnPlayClicked();
	UFUNCTION()
	void OnMenuClicked();

	// Sounds
	UPROPERTY(EditAnywhere)
	USoundBase* CameraChangeSound;
	
private:

	UPROPERTY()
	UAnomalySelectionBox* CurrentlySelectedBox;
	
};
