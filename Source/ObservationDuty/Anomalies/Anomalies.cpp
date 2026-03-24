// 


#include "Anomalies.h"

#include "ObservationDuty/Components/AnomalyComponent/AnomalyComponent.h"

void UAnomalies::MoveObject(UAnomalyComponent* Actor, bool bState)
{
	if (bState)
	{
		Actor->GetOwner()->SetActorLocation(Actor->GetOwner()->GetActorLocation() + FVector(200, 0, 0));
	}
	else
	{
		Actor->GetOwner()->SetActorLocation(Actor->GetOwner()->GetActorLocation() - FVector(200, 0, 0));
	}
}
