// 


#include "ODMainGameState.h"

#include "Kismet/GameplayStatics.h"
#include "ObservationDuty/Components/AnomalyComponent/AnomalyComponent.h"
#include "ObservationDuty/Pawns/MapCamera.h"
#include "ObservationDuty/Structs/AnomalyStruct.h"

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

void AODMainGameState::SpawnAnomaly()
{
	if (AvailableAnomalies.Num() == 0) {UE_LOG(LogTemp, Warning, TEXT("No Anomalies")) return;};
	if (AvailableAnomalies.Num() > 1)
	{
		int32 randNum = FMath::RandRange(0, AvailableAnomalies.Num() - 1);
		UE_LOG(LogTemp, Warning, TEXT("Spawning %d"), randNum);
		bool bound = AvailableAnomalies[randNum].AnomalyEvent.ExecuteIfBound(AvailableAnomalies[randNum].AssociatedActor, true);
		if (!bound)
		{
			UE_LOG(LogTemp, Warning, TEXT("EVENT NOT BOUND!"));
		}
		else
		{
			ActiveAnomalies.Add(AvailableAnomalies[randNum]);
			AvailableAnomalies.RemoveAt(randNum);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning 0"));
		bool bound = AvailableAnomalies[0].AnomalyEvent.ExecuteIfBound(AvailableAnomalies[0].AssociatedActor, true);
		if (!bound)
		{
			UE_LOG(LogTemp, Warning, TEXT("EVENT NOT BOUND!"));
		}
		else
		{
			ActiveAnomalies.Add(AvailableAnomalies[0]);
			AvailableAnomalies.RemoveAt(0);
		}
	}
}

void AODMainGameState::ReportAnomaly(EAnomalyType AnomalyType, AMapCamera* Camera)
{
	for (int i = 0; i < ActiveAnomalies.Num(); i++)
	{
		if (AnomalyType == ActiveAnomalies[i].AnomalyType && Camera == ActiveAnomalies[i].AssociatedCamera)
		{
			bool bound = ActiveAnomalies[i].AnomalyEvent.ExecuteIfBound(ActiveAnomalies[i].AssociatedActor, false);
			if (!bound)
			{
				UE_LOG(LogTemp, Warning, TEXT("EVENT NOT BOUND!"));
			}
			else
			{
				AvailableAnomalies.Add(ActiveAnomalies[i]);
				ActiveAnomalies.RemoveAt(i);
			}
		}
	}
}

void AODMainGameState::RegisterAnomalies(TArray<FAnomaly> Anomalies, UAnomalyComponent* AssociatedActor)
{
	UE_LOG(LogTemp, Display, TEXT("Registering Anomalies for %s"), *AssociatedActor->GetOwner()->GetActorNameOrLabel())
	for (FAnomaly& Anomaly : Anomalies)
	{
		UE_LOG(LogTemp, Display, TEXT("Registering Anomaly: %s"), *Anomaly.AnomalyName)
		if (AnomalyFunctions.Find(Anomaly.AnomalyName))
		{
			Anomaly.AnomalyEvent = *AnomalyFunctions.Find(Anomaly.AnomalyName);
			Anomaly.AssociatedActor = AssociatedActor;
			AvailableAnomalies.Add(Anomaly);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Could not find %s in Dictionary/Map (AnomalyFunctions), please add it or double check in AODMainGameState"), *Anomaly.AnomalyName)
		}
	}
}