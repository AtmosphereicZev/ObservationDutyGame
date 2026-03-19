// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MapCamera.generated.h"

struct FInputActionValue;
class AODMainGameState;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;

UCLASS()
class OBSERVATIONDUTY_API AMapCamera : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	// Inputs
	UPROPERTY(EditAnywhere)
	UInputMappingContext* MainMappingContext;
	UPROPERTY(EditAnywhere)
	UInputAction* NextCamera;	
	UPROPERTY(EditAnywhere)
	UInputAction* BackCamera;	
	
public:
	AMapCamera();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	/* ///////////////////////////////////////////////////////
	 *					   Input Functions
	 * //////////////////////////////////////////////////////*/	

	void NextCameraFunction(const FInputActionValue& Value);
	void PreviousCameraFunction(const FInputActionValue& Value);
	
private:

	/* ///////////////////////////////////////////////////////
	 *					 Private Properties
	 * //////////////////////////////////////////////////////*/

	UPROPERTY()
	AODMainGameState* GameState;
	
};
