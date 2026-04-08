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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCameraChanged);

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
	UPROPERTY(EditAnywhere)
	UInputAction* Pause;	
	
public:
	AMapCamera();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/* ///////////////////////////////////////////////////////
	 *					   Input Functions
	 * //////////////////////////////////////////////////////*/	

	void NextCameraFunction();
	void PreviousCameraFunction();
	void PauseFunction();

	/* ///////////////////////////////////////////////////////
	 *					   Getters/Setters
	 * //////////////////////////////////////////////////////*/	

	bool GetPreventInput() const {return bPreventInputs;}
	void SetPreventInput(bool Value){bPreventInputs = Value;}

	/* ///////////////////////////////////////////////////////
	 *					   Public Properties
	 * //////////////////////////////////////////////////////*/	

	// Name that will appear in hud when looking through camera.
	UPROPERTY(EditAnywhere)
	FString CameraName;
	
protected:
	virtual void BeginPlay() override;
	
private:

	/* ///////////////////////////////////////////////////////
	 *					 Private Properties
	 * //////////////////////////////////////////////////////*/

	UPROPERTY()
	AODMainGameState* GameState;
	bool bCanPause = false;
	// This is automatically true until changed on begin play.
	bool bPreventInputs = true;
	
};
