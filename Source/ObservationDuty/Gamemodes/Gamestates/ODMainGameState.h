// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ODMainGameState.generated.h"

class AMapCamera;
/**
 * 
 */
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

	UFUNCTION()
	AMapCamera* GetNextCamera(AMapCamera* CurrentCamera);
	UFUNCTION()
	AMapCamera* GetPreviousCamera(AMapCamera* CurrentCamera);

private:

	/* ///////////////////////////////////////////////////////
	 *					 Private Properties
	 * //////////////////////////////////////////////////////*/		

	UPROPERTY()
	TArray<AMapCamera*> MapCameras;
	TSubclassOf<AMapCamera> MapCameraClass;
	
};
