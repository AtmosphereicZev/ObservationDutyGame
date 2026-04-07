// 


#include "MapCamera.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AssetTypeActions/AssetDefinition_SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "ObservationDuty/Controllers/ODPlayerController.h"
#include "ObservationDuty/Gamemodes/Gamestates/ODMainGameState.h"
#include "ObservationDuty/HUD/ODHUD.h"


AMapCamera::AMapCamera()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Root);
}

void AMapCamera::BeginPlay()
{
	Super::BeginPlay();

	// Letting starting sequence play before giving the ability to pause.
	FTimerDelegate PauseDelegate;
	FTimerHandle PauseHandle;
	PauseDelegate.BindLambda([](bool* bCanPause)
	{
		*bCanPause = true;
	}, &bCanPause);
	GetWorldTimerManager().SetTimer(PauseHandle, PauseDelegate, 12.f, false);
	
	
	// Get Game State
	if (AODMainGameState* ODGameState = Cast<AODMainGameState>(GetWorld()->GetGameState()))
	{
		GameState = ODGameState;
	}
}

void AMapCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
		if (Subsystem == ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MainMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(NextCamera, ETriggerEvent::Started, this, &AMapCamera::NextCameraFunction);		
		EnhancedInputComponent->BindAction(BackCamera, ETriggerEvent::Started, this, &AMapCamera::PreviousCameraFunction);		
		EnhancedInputComponent->BindAction(Pause, ETriggerEvent::Started, this, &AMapCamera::PauseFunction);		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComponent is NULL or is not what its meant to be, check code and try again!"))
	}
}

void AMapCamera::NextCameraFunction()
{
	if (bPreventInputs){return;}
	AMapCamera* NextCameraActor = GameState->GetNextCamera(this);
	GetController()->Possess(NextCameraActor);
}

void AMapCamera::PreviousCameraFunction()
{
	if (bPreventInputs){return;}
	AMapCamera* PreviousCameraActor = GameState->GetPreviousCamera(this);
	GetController()->Possess(PreviousCameraActor);
}

void AMapCamera::PauseFunction()
{
	if (bPreventInputs){return;}
	if (bCanPause)
	{
		if (!UGameplayStatics::IsGamePaused(GetWorld()))
		{
			if (AODPlayerController* PC = GetController<AODPlayerController>())
			{
				PC->OnGamePaused.Broadcast(true);
			}
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		}
		else
		{
			if (AODPlayerController* PC = GetController<AODPlayerController>())
			{
				PC->OnGamePaused.Broadcast(false);
			}
			UGameplayStatics::SetGamePaused(GetWorld(), false);
		}
	}
}