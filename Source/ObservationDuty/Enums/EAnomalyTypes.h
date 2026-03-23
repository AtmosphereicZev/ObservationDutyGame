#pragma once
#include "ObservationDuty/Structs/FAnomalyTypes.h"


UENUM()
enum EAnomalyType
{
	ObjectManipulation,
	ExtraObject,
	ObjectDisappearance,
	CameraMalfunction,
	Shadow
};

