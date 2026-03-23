// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ObservationDuty/Actors/Anomalies/Anomalies.h"
#include "ObservationDuty/Enums/EAnomalyTypes.h"
#include "ODMainGameState.generated.h"

struct FAnomaly;
class AMapCamera;
class AAnomalyActor;
/**
 * 
 */

DECLARE_DELEGATE_TwoParams(FAnomalyDelegate, AAnomalyActor*, bool);

UCLASS()
class OBSERVATIONDUTY_API AODMainGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	AODMainGameState();
	
	/* ///////////////////////////////////////////////////////
	 *					  Public Functions
	 * //////////////////////////////////////////////////////*/

	/**
	 * Returns the next camera in order from the camera passed in.
	 */
	UFUNCTION()
	AMapCamera* GetNextCamera(AMapCamera* CurrentCamera);
	/**
	 * Returns the previous camera in order from the camera passed in.
	 */
	UFUNCTION()
	AMapCamera* GetPreviousCamera(AMapCamera* CurrentCamera);

	/**
	 * Registers every anomaly inside the array making them spawnable throughout
	 * the game.
	 * 
	 * @param Anomalies Anomalies you want to register
	 * @param AssociatedActor The AnomalyActor associated with the anomalies
	 */
	UFUNCTION()
	void RegisterAnomalies(TArray<FAnomaly> Anomalies, AAnomalyActor* AssociatedActor);
	/**
	 * Spawns a random anomaly
	 * @note This can be called within the editor.
	 */
	UFUNCTION(Exec)
	void SpawnAnomaly();
	/**
	 * Reports and resets the anomaly if there is any active anomaly of the given type
	 * on the passed in camera.
	 */
	UFUNCTION()
	void ReportAnomaly(EAnomalyType AnomalyType, AMapCamera* Camera);

	/* ///////////////////////////////////////////////////////
	 *					  Getters/Setters
	 * //////////////////////////////////////////////////////*/		

	UFUNCTION()
	TArray<FAnomalyTypes> GetAnomalyTypes(){return AnomalyTypes;}
	
protected:

	/* ///////////////////////////////////////////////////////
	 *					 Protected Properties
	 * //////////////////////////////////////////////////////*/			

	/* Spawnable Anomalies */
	TArray<FAnomaly> AvailableAnomalies;
	/* Active Anomalies, once reported will return to Available anomalies */
	TArray<FAnomaly> ActiveAnomalies;
	
private:

	/* ///////////////////////////////////////////////////////
	 *					 Private Properties
	 * //////////////////////////////////////////////////////*/		

	UPROPERTY()
	TArray<AMapCamera*> MapCameras;
	TSubclassOf<AMapCamera> MapCameraClass;

	/* Associated Functions for each anomaly by name. */
	TMap<FString, FAnomalyDelegate> AnomalyFunctions = {
		{"Move", FAnomalyDelegate::CreateStatic(&UAnomalies::MoveObject)}
	};

	/* Full String Names of each anomaly. (Mainly used for the HUD) */
	TArray<FAnomalyTypes> AnomalyTypes = {
		{ObjectManipulation, "Object Manipulation"},
		{ExtraObject, "Extra Object"},
		{ObjectDisappearance, "Object Disappearance"},
		{CameraMalfunction, "Camera Malfunction"},
		{Shadow, "Shadow"}
	};
	
};
