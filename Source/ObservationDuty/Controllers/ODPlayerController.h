// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ODPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePaused, bool, bPaused);


/**
 * 
 */
UCLASS()
class OBSERVATIONDUTY_API AODPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	/* ///////////////////////////////////////////////////////
	 *							Events
	 * //////////////////////////////////////////////////////*/	

	UPROPERTY()
	FOnGamePaused OnGamePaused;

	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnCameraChanged(APawn* UnPossessedPawn, APawn* NewPossessedPawn);
	
};
