// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnomalyActor.generated.h"

struct FAnomaly;
class AODMainGameState;

UCLASS()
class OBSERVATIONDUTY_API AAnomalyActor : public AActor
{
	GENERATED_BODY()

public:
	AAnomalyActor();

	// Actor Root Component
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	/* ///////////////////////////////////////////////////////
	 *					 Public Properties
	 * //////////////////////////////////////////////////////*/

	UPROPERTY(EditAnywhere, Category="Anomalies")
	TArray<FAnomaly> SpawnableAnomalies;
	
protected:
	virtual void BeginPlay() override;
	
private:

	/* ///////////////////////////////////////////////////////
	 *					 Private Properties
	 * //////////////////////////////////////////////////////*/	

	UPROPERTY()
	AODMainGameState* GameState;
	
};
