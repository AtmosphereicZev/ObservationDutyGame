// 


#include "Anomalies.h"

void UAnomalies::MoveObject(AAnomalyActor* Actor, bool bState)
{
	if (bState)
	{
		Actor->SetActorLocation(Actor->GetActorLocation() + FVector(200, 0, 0));
	}
	else
	{
		Actor->SetActorLocation(Actor->GetActorLocation() - FVector(200, 0, 0));
	}
}
