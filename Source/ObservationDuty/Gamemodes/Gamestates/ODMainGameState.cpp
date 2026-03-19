// 


#include "ODMainGameState.h"

#include "Kismet/GameplayStatics.h"
#include "ObservationDuty/Pawns/MapCamera.h"

AODMainGameState::AODMainGameState()
{
	ConstructorHelpers::FClassFinder<AMapCamera> MapCameraClassRef = ConstructorHelpers::FClassFinder<AMapCamera>(TEXT("/Game/Blueprints/Actors/BP_MapCamera"));
	if (MapCameraClassRef.Succeeded())
	{
		MapCameraClass = MapCameraClassRef.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found No Map Cameras."))
	}
}

void AODMainGameState::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), MapCameraClass, FoundCameras);
	for (AActor* Actor : FoundCameras)
	{
		if (AMapCamera* CameraActor = Cast<AMapCamera>(Actor))
		{
			MapCameras.Add(CameraActor);
		}
	}
}

AMapCamera* AODMainGameState::GetNextCamera(AMapCamera* CurrentCamera)
{
	for (AMapCamera* Camera : MapCameras)
	{
		if (Camera == CurrentCamera)
		{
			if (MapCameras.Find(Camera) == MapCameras.Num() - 1)
			{
				return MapCameras[0];
			}
			else
			{
				return MapCameras[MapCameras.Find(Camera) + 1];
			}
		}
	}
	return nullptr;
}


AMapCamera* AODMainGameState::GetPreviousCamera(AMapCamera* CurrentCamera)
{
	for (AMapCamera* Camera : MapCameras)
	{
		if (Camera == CurrentCamera)
		{
			if (MapCameras.Find(Camera) == 0)
			{
				return MapCameras[MapCameras.Num() - 1];
			}
			else
			{
				return MapCameras[MapCameras.Find(Camera) - 1];
			}
		}
	}
	return nullptr;
}
