// 


#include "ODMainGameState.h"

#include "Kismet/GameplayStatics.h"
#include "ObservationDuty/Components/AnomalyComponent/AnomalyComponent.h"
#include "ObservationDuty/Pawns/MapCamera.h"
#include "ObservationDuty/Structs/AnomalyStruct.h"
#include "Sound/AmbientSound.h"

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

	// 11-Minute Game Timer.
	FTimerDelegate GameTimerDelegate;
	GameTimerDelegate.BindUFunction(this, "GameEnd");
	// 660 = 11 minutes.
	GetWorldTimerManager().SetTimer(GameTimer, GameTimerDelegate, 660.0f, false);

	// Prep Phase - giving the player minute to memorize the map before anomalies start
	// spawning every minute.
	FTimerHandle PrepPhaseHandle;
	FTimerDelegate PrepPhaseDelegate;
	PrepPhaseDelegate.BindUFunction(this, "EndPrepPhase");
	GetWorldTimerManager().SetTimer(PrepPhaseHandle, PrepPhaseDelegate, 60.0f, false);

	// Enable Map Ambience
	FTimerDelegate AmbienceDelegate;
	FTimerHandle AmbienceHandle;
	AmbienceDelegate.BindLambda([this]()
	{
		TArray<AActor*> FoundSounds;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAmbientSound::StaticClass(), FoundSounds);
		for (AActor* Sound : FoundSounds)
		{
			if (AAmbientSound* CastedSound = Cast<AAmbientSound>(Sound))
			{
				CastedSound->FadeIn(10,1);
			}
		}
	});
	GetWorldTimerManager().SetTimer(AmbienceHandle, AmbienceDelegate, 10.0f, false);
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
	if (AvailableAnomalies.Num() == 0) {UE_LOG(LogTemp, Warning, TEXT("No Anomalies")) return;}
	if (AvailableAnomalies.Num() > 1)
	{
		// Anomalies that aren't on the active camera.
		TArray<FAnomaly> ValidAnomalies;
		for (int i = 0; i < AvailableAnomalies.Num(); i++)
		{
			if (AvailableAnomalies[i].AssociatedCamera != CurrentlyControlledCamera)
			{
				ValidAnomalies.Add(AvailableAnomalies[i]);
			}
		}
		if (ValidAnomalies.Num() == 0) return;
		if (ValidAnomalies.Num() > 1)
		{
			int32 randNum = FMath::RandRange(0, ValidAnomalies.Num() - 1);
			UE_LOG(LogTemp, Warning, TEXT("Spawning Anomaly: %s in %s"), *ValidAnomalies[randNum].AnomalyName, *ValidAnomalies[randNum].AssociatedCamera->CameraName);
			bool bound = ValidAnomalies[randNum].AnomalyEvent.ExecuteIfBound(ValidAnomalies[randNum].AssociatedActor, ValidAnomalies[randNum].AssociatedActors, true);
			if (!bound)
			{
				UE_LOG(LogTemp, Warning, TEXT("EVENT NOT BOUND!"));
			}
			else
			{
				for (int i = 0; i < AvailableAnomalies.Num(); i++)
				{
					if (AvailableAnomalies[i].AnomalyName == ValidAnomalies[randNum].AnomalyName && AvailableAnomalies[i].AssociatedActor == ValidAnomalies[randNum].AssociatedActor)
					{
						ActiveAnomalies.Add(AvailableAnomalies[i]);
						AvailableAnomalies.RemoveAt(i);
						CheckAnomalyCount();
						return;
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("There are no more then 1 valid anomaly to spawn"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("There are not enough anomalies registered to spawn a random one, please add more in your map!"))
	}
}

void AODMainGameState::ReportAnomaly(EAnomalyType AnomalyType, AMapCamera* Camera)
{
	for (int i = 0; i < ActiveAnomalies.Num(); i++)
	{
		if (AnomalyType == ActiveAnomalies[i].AnomalyType && Camera == ActiveAnomalies[i].AssociatedCamera)
		{
			OnSuccessfullyReportedAnomaly.Broadcast();
			bool bound = ActiveAnomalies[i].AnomalyEvent.ExecuteIfBound(ActiveAnomalies[i].AssociatedActor, ActiveAnomalies[i].AssociatedActors, false);
			if (!bound)
			{
				UE_LOG(LogTemp, Warning, TEXT("EVENT NOT BOUND!"));
			}
			else
			{
				AvailableAnomalies.Add(ActiveAnomalies[i]);
				ActiveAnomalies.RemoveAt(i);
				return;
			}
		}
	}
}

void AODMainGameState::StopMapAmbience()
{
	TArray<AActor*> FoundSounds;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAmbientSound::StaticClass(), FoundSounds);
	for (AActor* Sound : FoundSounds)
	{
		if (AAmbientSound* CastedSound = Cast<AAmbientSound>(Sound))
		{
			CastedSound->FadeOut(3, 1);
		}
	}
}

void AODMainGameState::GameEnd()
{
	GetWorldTimerManager().ClearTimer(AnomalyTimer);
	StopMapAmbience();
	OnGameWon.Broadcast();
}

void AODMainGameState::GameLost()
{
	GetWorldTimerManager().ClearTimer(AnomalyTimer);
	GetWorldTimerManager().ClearTimer(GameTimer);
	TArray<AActor*> FoundSounds;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAmbientSound::StaticClass(), FoundSounds);
	for (AActor* Sound : FoundSounds)
	{
		if (AAmbientSound* CastedSound = Cast<AAmbientSound>(Sound))
		{
			CastedSound->Stop();
		}
	}
	OnGameLost.Broadcast();
}

void AODMainGameState::EndPrepPhase()
{
	UE_LOG(LogTemp, Warning, TEXT("Prep Phrase Over - Spawning Anomaly"));
	SpawnAnomaly();
	FTimerDelegate AnomalyDelegate;
	AnomalyDelegate.BindUFunction(this, FName("SpawnAnomaly"));
	GetWorldTimerManager().SetTimer(AnomalyTimer, AnomalyDelegate, 60.0f, true);
	CheckAnomalyCount();
}

void AODMainGameState::CheckAnomalyCount()
{
	if (ActiveAnomalies.Num() >= 4)
	{
		if (ActiveAnomalies.Num() >= 5)
		{
			GameLost();
		}
		else
		{
			OnAnomalyOverload.Broadcast();
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
