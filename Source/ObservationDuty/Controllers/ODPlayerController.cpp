// 


#include "ODPlayerController.h"

#include "ObservationDuty/Gamemodes/Gamestates/ODMainGameState.h"
#include "ObservationDuty/HUD/ODHUD.h"
#include "ObservationDuty/Pawns/MapCamera.h"

void AODPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);
	OnPossessedPawnChanged.AddDynamic(this, &AODPlayerController::OnCameraChanged);
}

void AODPlayerController::OnCameraChanged(APawn* UnPossessedPawn, APawn* NewPossessedPawn)
{
	if (AODMainGameState* GameState = GetWorld()->GetGameState<AODMainGameState>())
	{
		if (AMapCamera* Camera = Cast<AMapCamera>(NewPossessedPawn))
		{
			GameState->CurrentlyControlledCamera = Camera;
			if (AODHUD* HUD = GetHUD<AODHUD>())
			{
				HUD->GetMainWidget()->SetCameraText(Camera->CameraName);
			}
		}
	}
}
