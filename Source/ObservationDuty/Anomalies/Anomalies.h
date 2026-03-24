// 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Anomalies.generated.h"

class UAnomalyComponent;
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
	static void MoveObject(UAnomalyComponent* Actor, bool bState);
	
protected:

	
	
};
