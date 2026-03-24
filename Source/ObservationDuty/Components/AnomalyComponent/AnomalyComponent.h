// 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnomalyComponent.generated.h"


class AODMainGameState;
struct FAnomaly;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OBSERVATIONDUTY_API UAnomalyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAnomalyComponent();

	/* ///////////////////////////////////////////////////////
	 *					 Public Properties
	 * //////////////////////////////////////////////////////*/

	UPROPERTY(EditAnywhere, Category="Anomalies")
	TArray<FAnomaly> SpawnableAnomalies;
	
protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	AODMainGameState* GameState;
	
};
