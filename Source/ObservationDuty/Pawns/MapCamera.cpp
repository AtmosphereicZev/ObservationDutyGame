// 


#include "MapCamera.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ObservationDuty/Gamemodes/Gamestates/ODMainGameState.h"


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
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComponent is NULL or is not what its meant to be, check code and try again!"))
	}
}

void AMapCamera::NextCameraFunction()
{
	AMapCamera* NextCameraActor = GameState->GetNextCamera(this);
	GetController()->Possess(NextCameraActor);
}

void AMapCamera::PreviousCameraFunction()
{
	AMapCamera* PreviousCameraActor = GameState->GetPreviousCamera(this);
	GetController()->Possess(PreviousCameraActor);
}
