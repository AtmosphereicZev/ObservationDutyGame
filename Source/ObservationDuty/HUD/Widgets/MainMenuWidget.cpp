// 


#include "MainMenuWidget.h"

#include "ObservationDuty/ObservationDutyGameInstance.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Starting Animation
	if (GetWorld()->GetGameInstance<UObservationDutyGameInstance>()->bPlayMenuStartAnimation)
	{
		PlayAnimation(StartAnimation);
		GetWorld()->GetGameInstance<UObservationDutyGameInstance>()->bPlayMenuStartAnimation = false;
	}
	else
	{
		PlayAnimation(TransitionAnimation);
	}
}
