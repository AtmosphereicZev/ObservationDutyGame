// 


#include "Anomalies.h"

#include "Components/DecalComponent.h"
#include "Components/PostProcessComponent.h"
#include "Engine/DecalActor.h"
#include "Kismet/GameplayStatics.h"
#include "ObservationDuty/Components/AnomalyComponent/AnomalyComponent.h"

void UAnomalies::MoveObject(UAnomalyComponent* Actor, TArray<AActor*> AssociatedActors, bool bState)
{
	TArray<UActorComponent*> Meshes = Actor->GetOwner()->GetComponentsByTag(UStaticMeshComponent::StaticClass(), "Mesh");
	UE_LOG(LogTemp, Warning, TEXT("Anomaly Testing: Called Move"))
	UE_LOG(LogTemp, Warning, TEXT("Anomaly Testing: Found %i Meshes"), Meshes.Num())
	for (UActorComponent* Mesh : Meshes)
	{
		if (UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(Mesh))
		{
			if (StaticMesh->IsVisible())
			{
				StaticMesh->SetVisibility(false);
			}
			else
			{
				StaticMesh->SetVisibility(true);
			}
		}
	}
}

void UAnomalies::Vanish(UAnomalyComponent* Actor, TArray<AActor*> AssociatedActors, bool bState)
{
	if (bState)
	{
		Actor->GetOwner()->GetComponentByClass<UStaticMeshComponent>()->SetVisibility(false);
		for (AActor* AssociatedActor : AssociatedActors)
		{
			if (AssociatedActor)
			{
				if (UStaticMeshComponent* Mesh = AssociatedActor->GetComponentByClass<UStaticMeshComponent>())
				{
					Mesh->SetVisibility(false);
				}
			}
		}
	}
	else
	{
		Actor->GetOwner()->GetComponentByClass<UStaticMeshComponent>()->SetVisibility(true);
		for (AActor* AssociatedActor : AssociatedActors)
		{
			if (AssociatedActor)
			{
				if (UStaticMeshComponent* Mesh = AssociatedActor->GetComponentByClass<UStaticMeshComponent>())
				{
					Mesh->SetVisibility(true);
				}
			}
		}
	}
}

void UAnomalies::VanishSprite(UAnomalyComponent* Actor, TArray<AActor*> AssociatedActors, bool bState)
{
	if (bState)
	{
		if (ADecalActor* Shadow = Cast<ADecalActor>(Actor->GetOwner()))
		{
			Shadow->GetDecal()->SetVisibility(false);
		}
	}
	else
	{
		if (ADecalActor* Shadow = Cast<ADecalActor>(Actor->GetOwner()))
		{
			Shadow->GetDecal()->SetVisibility(true);
		}
	}
}

void UAnomalies::Appear(UAnomalyComponent* Actor, TArray<AActor*> AssociatedActors, bool bState)
{
	if (bState)
	{
		Actor->GetOwner()->GetComponentByClass<UStaticMeshComponent>()->SetVisibility(true);
		for (AActor* AssociatedActor : AssociatedActors)
		{
			if (AssociatedActor)
			{
				if (UStaticMeshComponent* Mesh = AssociatedActor->GetComponentByClass<UStaticMeshComponent>())
				{
					Mesh->SetVisibility(true);
				}
			}
		}
	}
	else
	{
		Actor->GetOwner()->GetComponentByClass<UStaticMeshComponent>()->SetVisibility(false);
		for (AActor* AssociatedActor : AssociatedActors)
		{
			if (AssociatedActor)
			{
				if (UStaticMeshComponent* Mesh = AssociatedActor->GetComponentByClass<UStaticMeshComponent>())
				{
					Mesh->SetVisibility(false);
				}
			}
		}
	}
}

void UAnomalies::Malfunction(UAnomalyComponent* Actor, TArray<AActor*> AssociatedActors, bool bState)
{
	if (bState)
	{
		if (APostProcessVolume* PostProcessVolume = Cast<APostProcessVolume>(Actor->GetOwner()))
		{
			PostProcessVolume->bEnabled = true;
		}
	}
	else
	{
		if (APostProcessVolume* PostProcessVolume = Cast<APostProcessVolume>(Actor->GetOwner()))
		{
			PostProcessVolume->bEnabled = false;
		}
	}
}

void UAnomalies::TurnOnTV(UAnomalyComponent* Actor, TArray<AActor*> AssociatedActors, bool bState)
{
	TArray<UActorComponent*> Screen = Actor->GetOwner()->GetComponentsByTag(UStaticMeshComponent::StaticClass(), "Screen");
	if (bState)
	{
		if (UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Screen[0]))
		{
			Mesh->SetVisibility(true);
		}
	}
	else
	{
		if (UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Screen[0]))
		{
			Mesh->SetVisibility(false);
		}
	}
}

void UAnomalies::RotateRegisterShelf(UAnomalyComponent* Actor, TArray<AActor*> AssociatedActors, bool bState)
{
	Actor->GetOwner()->SetActorRotation(Actor->GetOwner()->GetActorRotation() + FRotator(0, 180, 0));
	for (AActor* AssociatedActor : AssociatedActors)
	{
		AssociatedActor->SetActorRotation(Actor->GetOwner()->GetActorRotation() + FRotator(0, 180, 0));
	}
}

void UAnomalies::Shadow(UAnomalyComponent* Actor, TArray<AActor*> AssociatedActors, bool bState)
{
	if (bState)
	{
		if (ADecalActor* Shadow = Cast<ADecalActor>(Actor->GetOwner()))
		{
			Shadow->GetDecal()->SetVisibility(true);
		}
	}
	else
	{
		if (ADecalActor* Shadow = Cast<ADecalActor>(Actor->GetOwner()))
		{
			Shadow->GetDecal()->SetVisibility(false);
		}
	}
}
