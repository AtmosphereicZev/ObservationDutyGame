// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ObservationDuty/Anomalies/Anomalies.h"
#include "ObservationDuty/Enums/EAnomalyTypes.h"
#include "ODMainGameState.generated.h"

class UAnomalyComponent;
struct FAnomaly;
class AMapCamera;
/**
 * 
 */

DECLARE_DELEGATE_ThreeParams(FAnomalyDelegate, UAnomalyComponent*, TArray<AActor*>, bool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSuccessfullyReportedAnomaly);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameWon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameLost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnomalyOverload);

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
	void RegisterAnomalies(TArray<FAnomaly> Anomalies, UAnomalyComponent* AssociatedActor);
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
	/**
	 * Fades out all ambience in the current map.
	 */
	UFUNCTION(BlueprintCallable)
	void StopMapAmbience();

	/* ///////////////////////////////////////////////////////
	 *					  Getters/Setters
	 * //////////////////////////////////////////////////////*/		

	UFUNCTION()
	TArray<FAnomalyTypes> GetAnomalyTypes(){return AnomalyTypes;}

	/* ///////////////////////////////////////////////////////
	 *					  Public Properties
	 * //////////////////////////////////////////////////////*/

	UPROPERTY()
	AMapCamera* CurrentlyControlledCamera;

	/* ///////////////////////////////////////////////////////
	 *						   Events
	 * //////////////////////////////////////////////////////*/

	UPROPERTY()
	FOnSuccessfullyReportedAnomaly OnSuccessfullyReportedAnomaly;
	UPROPERTY()
	FOnGameWon OnGameWon;
	UPROPERTY()
	FOnGameLost OnGameLost;
	UPROPERTY()
	FOnAnomalyOverload OnAnomalyOverload;
	
protected:

	/* ///////////////////////////////////////////////////////
	 *					 Protected Properties
	 * //////////////////////////////////////////////////////*/			

	/* Spawnable Anomalies */
	TArray<FAnomaly> AvailableAnomalies;
	/* Active Anomalies, once reported will return to Available anomalies */
	TArray<FAnomaly> ActiveAnomalies;

	/* ///////////////////////////////////////////////////////
	 *					 Protected Functions
	 * //////////////////////////////////////////////////////*/			

	UFUNCTION()
	void GameEnd();
	UFUNCTION()
	void GameLost();
	UFUNCTION()
	void EndPrepPhase();
	UFUNCTION()
	void CheckAnomalyCount();
	
private:

	/* ///////////////////////////////////////////////////////
	 *					 Private Properties
	 * //////////////////////////////////////////////////////*/		

	// Game timer that starts at the beginning of the game, lasts 13 minutes and gets
	// cleared when losing.
	UPROPERTY()
	FTimerHandle GameTimer;
	// Handle that spawns anomalies every minute
	// NOTE - Isn't used until 3 minutes after the game starts.
	UPROPERTY()
	FTimerHandle AnomalyTimer;
	
	UPROPERTY()
	TArray<AMapCamera*> MapCameras;
	TSubclassOf<AMapCamera> MapCameraClass;

	/* Associated Functions for each anomaly by name. */
	TMap<FString, FAnomalyDelegate> AnomalyFunctions = {
		{"Move", FAnomalyDelegate::CreateStatic(&UAnomalies::MoveObject)},
		{"Vanish", FAnomalyDelegate::CreateStatic(&UAnomalies::Vanish)},
		{"VanishSprite", FAnomalyDelegate::CreateStatic(&UAnomalies::VanishSprite)},
		{"Appear", FAnomalyDelegate::CreateStatic(&UAnomalies::Appear)},
		{"Shadow", FAnomalyDelegate::CreateStatic(&UAnomalies::Shadow)},
		{"Malfunction", FAnomalyDelegate::CreateStatic(&UAnomalies::Malfunction)},
		{"TurnOnTV", FAnomalyDelegate::CreateStatic(&UAnomalies::TurnOnTV)},
		{"RotateRegisterShelf", FAnomalyDelegate::CreateStatic(&UAnomalies::RotateRegisterShelf)}
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
