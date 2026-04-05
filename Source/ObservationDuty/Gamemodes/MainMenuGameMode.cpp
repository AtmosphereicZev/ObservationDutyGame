// 


#include "MainMenuGameMode.h"

#include "GameFramework/GameSession.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	Controller->SetShowMouseCursor(true);
}
