// 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "FAnomalyTypes.generated.h"

enum EAnomalyType : int;

USTRUCT()
struct FAnomalyTypes
{
	GENERATED_BODY()

	EAnomalyType Type;
	FString Name;
};
