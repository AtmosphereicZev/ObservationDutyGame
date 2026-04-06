// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Widgets/MainWidget.h"
#include "ODHUD.generated.h"

class AODMainGameState;
/**
 * 
 */
UCLASS()
class OBSERVATIONDUTY_API AODHUD : public AHUD
{
	GENERATED_BODY()

public:
	AODHUD();
	
	/* ///////////////////////////////////////////////////////
	 *					 Public Functions
	 * //////////////////////////////////////////////////////*/		

	UFUNCTION()
	UMainWidget* GetMainWidget() const {return ActiveMainWidget;}
	UFUNCTION()
	void ReportAnomaly(EAnomalyType AnomalyType);
	UFUNCTION()
	void NextCamera();
	UFUNCTION()
	void PreviousCamera();
	UFUNCTION()
	void ResumeGame();
	
protected:
	virtual void BeginPlay() override;

private:

	/* ///////////////////////////////////////////////////////
	 *					 Private Properties
	 * //////////////////////////////////////////////////////*/		

	UPROPERTY()
	TSubclassOf<UUserWidget> MainWidgetClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> AnomalySelectionBoxClass;
	UPROPERTY()
	UMainWidget* ActiveMainWidget;
	UPROPERTY()
	AODMainGameState* GameState;
	
};
