// 


#include "MainMenuHUD.h"

AMainMenuHUD::AMainMenuHUD()
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetRef = ConstructorHelpers::FClassFinder<UUserWidget>(TEXT("/Game/Blueprints/Widgets/WBP_MainMenu"));
	if (MainMenuWidgetRef.Succeeded())
	{
		MainMenuWidgetClass = MainMenuWidgetRef.Class;
	}
}

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	ActiveMainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
	ActiveMainMenuWidget->AddToViewport();
}
