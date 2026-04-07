// 


#include "MainWidget.h"

#include "AnomalySelectionBox.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "ObservationDuty/Gamemodes/Gamestates/ODMainGameState.h"
#include "ObservationDuty/HUD/ODHUD.h"
#include "ObservationDuty/Pawns/MapCamera.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	RA_ReportButton->SetIsEnabled(false);
	RA_ReportButton->OnPressed.AddDynamic(this, &UMainWidget::OnReportButtonClicked);
	NextCameraButton->OnPressed.AddDynamic(this, &UMainWidget::OnNextCameraClicked);
	PreviousCameraButton->OnPressed.AddDynamic(this, &UMainWidget::OnPreviousCameraClicked);
	B_Play->OnPressed.AddDynamic(this, &UMainWidget::OnPlayClicked);
	B_Menu->OnPressed.AddDynamic(this, &UMainWidget::OnMenuClicked);
	
	// Starting Animation
	PlayAnimation(LoadAnimation);
}

void UMainWidget::SetupWidget()
{
	if (AODMainGameState* GameState = GetWorld()->GetGameState<AODMainGameState>())
	{
		TArray<FAnomalyTypes> AnomalyTypes = GameState->GetAnomalyTypes();
		for (FAnomalyTypes AnomalyType : AnomalyTypes)
		{
			UAnomalySelectionBox* NewSelectionBox = CreateWidget<UAnomalySelectionBox>(GetWorld(), AnomalySelectionBoxClass);
			NewSelectionBox->SetupSelectionBox(AnomalyType.Name, AnomalyType.Type);
			NewSelectionBox->OnClickedDelegate.BindUFunction(this, "OnSelectionBoxClicked");
			RA_SB->AddChild(NewSelectionBox);
		}
	}
}

void UMainWidget::SetCameraText(FString Name)
{
	CameraName->SetText(FText::FromString(Name));
}

void UMainWidget::OnSelectionBoxClicked(UAnomalySelectionBox* BoxClicked)
{
	if (CurrentlySelectedBox)
	{
		if (CurrentlySelectedBox == BoxClicked)
		{
			RA_ReportButton->SetIsEnabled(false);
			CurrentlySelectedBox->UnhighlightBox();
			CurrentlySelectedBox = nullptr;
		}
		else
		{
			RA_ReportButton->SetIsEnabled(true);
			CurrentlySelectedBox->UnhighlightBox();
			CurrentlySelectedBox = BoxClicked;
			CurrentlySelectedBox->HighlightBox();
		}
	}
	else
	{
		RA_ReportButton->SetIsEnabled(true);
		CurrentlySelectedBox = BoxClicked;
		CurrentlySelectedBox->HighlightBox();
	}
}

void UMainWidget::OnReportButtonClicked()
{
	RA_ReportButton->SetIsEnabled(false);
	TArray<UWidget*> SelectionBoxes = RA_SB->GetAllChildren();
	for (UWidget* SelectionBox : SelectionBoxes)
	{
		if (UAnomalySelectionBox* Box = Cast<UAnomalySelectionBox>(SelectionBox))
		{
			Box->Button->SetIsEnabled(false);
		}
	}
	CurrentlySelectedBox->UnhighlightBox();
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, "ReportAnomaly", CurrentlySelectedBox->GetSelectionType());
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 10.0f, false);
	CurrentlySelectedBox = nullptr;
}

void UMainWidget::ReportAnomaly(EAnomalyType AnomalyType)
{
	HUD->ReportAnomaly(AnomalyType);
	RA_ReportButton->SetIsEnabled(false);
	TArray<UWidget*> SelectionBoxes = RA_SB->GetAllChildren();
	for (UWidget* SelectionBox : SelectionBoxes)
	{
		if (UAnomalySelectionBox* Box = Cast<UAnomalySelectionBox>(SelectionBox))
		{
			Box->Button->SetIsEnabled(true);
		}
	}
}

void UMainWidget::OnCameraChanged(APawn* OldPawn, APawn* NewPawn)
{
	if (CurrentlySelectedBox)
	{
		RA_ReportButton->SetIsEnabled(false);
		CurrentlySelectedBox->UnhighlightBox();
		CurrentlySelectedBox = nullptr;
	}

	PlayAnimation(SwitchAnimation);
	PlaySound(CameraChangeSound);
}

void UMainWidget::ChangeToPaused(bool bPaused)
{
	if (bPaused)
	{
		if (bAllowUISwitch)
		{
			PlayAnimation(PauseAnim);
			PlaySound(CameraChangeSound);
			UISwitcher->SetActiveWidgetIndex(1);
		}
	}
	else
	{
		if (bAllowUISwitch)
		{
			PlayAnimation(PauseAnim);
			PlaySound(CameraChangeSound);
			UISwitcher->SetActiveWidgetIndex(0);
		}
	}
}

void UMainWidget::OnNextCameraClicked()
{
	HUD->NextCamera();
}

void UMainWidget::OnPreviousCameraClicked()
{
	HUD->PreviousCamera();
}

void UMainWidget::OnPlayClicked()
{
	HUD->ResumeGame();
}

void UMainWidget::OnMenuClicked()
{
	HUD->ReturnToMenu();
}