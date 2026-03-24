// 


#include "AnomalyComponent.h"
#include "ObservationDuty/Structs/AnomalyStruct.h"
#include "ObservationDuty/Gamemodes/Gamestates/ODMainGameState.h"


UAnomalyComponent::UAnomalyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UAnomalyComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AODMainGameState* GameStateRef = Cast<AODMainGameState>(GetWorld()->GetGameState()))
	{
		GameState = GameStateRef;
	}

	GameState->RegisterAnomalies(SpawnableAnomalies, this);
}

