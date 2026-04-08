// 

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ObservationDutyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATIONDUTY_API UObservationDutyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	bool bPlayMenuStartAnimation = true;
	
};
