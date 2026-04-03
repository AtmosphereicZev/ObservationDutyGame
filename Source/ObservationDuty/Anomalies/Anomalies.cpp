// 


#include "Anomalies.h"

#include "Kismet/GameplayStatics.h"
#include "ObservationDuty/Components/AnomalyComponent/AnomalyComponent.h"

void UAnomalies::MoveObject(UAnomalyComponent* Actor, TArray<AActor*> AssociatedActors, bool bState)
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

void UAnomalies::Vanish(UAnomalyComponent* Actor, TArray<AActor*> AssociatedActors, bool bState)
{
	if (bState)
	{
		Actor->GetOwner()->GetComponentByClass<UStaticMeshComponent>()->SetVisibility(false);
	}
	else
	{
		Actor->GetOwner()->GetComponentByClass<UStaticMeshComponent>()->SetVisibility(true);
	}
}
