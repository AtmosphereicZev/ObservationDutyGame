// 

#pragma once

#include "CoreMinimal.h"
#include "ObservationDuty/Actors/AnomalyActor.h"
#include "UObject/Object.h"
#include "Anomalies.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATIONDUTY_API UAnomalies : public UObject
{
	GENERATED_BODY()

	/*
	 * Here is where all the anomaly functions are stored. if you want to make your
	 * own anomaly, make the function here then give it a name in AODMainGameState in the
	 * AnomalyFunctions map. Then when dragging in the AnomalyActor into the world, add
	 * a spawnable anomaly with the same name you gave it inside the map.
	 */
	
public:

	// Functions
	UFUNCTION()
	static void MoveObject(AAnomalyActor* Actor, bool bState);
	
protected:

	
	
};
