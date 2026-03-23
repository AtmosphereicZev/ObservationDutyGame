// 


#include "AnomalyActor.h"
#include "ObservationDuty/Structs/AnomalyStruct.h"


AAnomalyActor::AAnomalyActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

void AAnomalyActor::BeginPlay()
{
	Super::BeginPlay();

	if (AODMainGameState* GameStateRef = Cast<AODMainGameState>(GetWorld()->GetGameState()))
	{
		GameState = GameStateRef;
	}

	GameState->RegisterAnomalies(SpawnableAnomalies, this);
}
