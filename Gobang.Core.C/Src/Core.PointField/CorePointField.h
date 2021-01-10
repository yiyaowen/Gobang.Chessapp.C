#ifndef CORE_POINT_FIELD_H
#define CORE_POINT_FIELD_H

#include "CoreDefinitions.h"
#include "CoreRenjuGroupList.h"
#include "CoreRenjuRange.h"

CorePoint getCorePointFromPointFieldAlgorithm(RenjuGroupList* list);

CorePointList* getNewEncapsulatedPointListOfPoint(CorePoint point);

#define CORE_POINT_FIELD_BASE_SCORE		0
#define CORE_POINT_FIELD_INVALID_SCORE	0
#define CORE_POINT_FIELD_FAVORS_SCORE	100
#define CORE_POINT_FIELD_ADVERSE_SCORE	100

#endif