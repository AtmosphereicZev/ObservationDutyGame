// 


#include "ODHUD.h"

#include "ObservationDuty/Gamemodes/Gamestates/ODMainGameState.h"
#include "ObservationDuty/Pawns/MapCamera.h"

AODHUD::AODHUD()
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainWidgetRef = ConstructorHelpers::FClassFinder<UUserWidget>(TEXT("/Game/Blueprints/Widgets/WBP_MainWidget"));
	ConstructorHelpers::FClassFinder<UUserWidget> AnomalySelectionBoxRef = ConstructorHelpers::FClassFinder<UUserWidget>(TEXT("/Game/Blueprints/Widgets/WBP_AnomalySelectionBox"));
	if (MainWidgetRef.Succeeded())
	{
		MainWidgetClass = MainWidgetRef.Class;
		AnomalySelectionBoxClass = AnomalySelectionBoxRef.Class;
	}	
}

void AODHUD::BeginPlay()
{
	Super::BeginPlay();

	ActiveMainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetClass);
	if (AnomalySelectionBoxClass)
	{
		ActiveMainWidget->AnomalySelectionBoxClass = AnomalySelectionBoxClass;
		ActiveMainWidget->HUD = this;
		ActiveMainWidget->SetupWidget();
		ActiveMainWidget->AddToViewport();
		GetOwningPlayerController()->OnPossessedPawnChanged.AddDynamic(ActiveMainWidget, &UMainWidget::UnselectAnomalySelection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AnomalySelectionBox in HUD is not valid!"))
	}

	if (AODMainGameState* GameStateRef = Cast<AODMainGameState>(GetWorld()->GetGameState()))
	{
		GameState = GameStateRef;
	}

}

void AODHUD::ReportAnomaly(EAnomalyType AnomalyType)
{
	if (AMapCamera* Camera = Cast<AMapCamera>(GetOwningPlayerController()->GetPawn()))
	{
		GameState->ReportAnomaly(AnomalyType, Camera);
	}
}

void AODHUD::NextCamera()
{
	if (AMapCamera* Camera = Cast<AMapCamera>(GetOwningPlayerController()->GetPawn()))
	{
		Camera->NextCameraFunction();
	}
}

void AODHUD::PreviousCamera()
{
	if (AMapCamera* Camera = Cast<AMapCamera>(GetOwningPlayerController()->GetPawn()))
	{
		Camera->PreviousCameraFunction();
	}
}
