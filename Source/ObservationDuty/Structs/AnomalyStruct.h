// 

#pragma once

#include "CoreMinimal.h"
#include "ObservationDuty/Enums/EAnomalyTypes.h"
#include "ObservationDuty/Gamemodes/Gamestates/ODMainGameState.h"
#include "UObject/Class.h"
#include "AnomalyStruct.generated.h"

class AMapCamera;

USTRUCT()
struct FAnomaly
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FString AnomalyName;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EAnomalyType> AnomalyType;
	UPROPERTY(EditAnywhere)
	AMapCamera* AssociatedCamera;
	UPROPERTY()
	UAnomalyComponent* AssociatedActor;
	FAnomalyDelegate AnomalyEvent;
};