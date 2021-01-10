#ifndef RENJU_RANGE_GROUP_H
#define RENJU_RANGE_GROUP_H

#include "CoreRenjuRange.h"
#include "CoreRenjuGroupList.h"

typedef struct type_RenjuRangeGroup {
    int renjuRangeCount;
    RenjuRange* renjuRanges;
} RenjuRangeGroup;

RenjuRangeGroup* getNewDefaultRenjuRangeGroupInRenjuGroupListOfPoint(RenjuGroupList* list, CorePoint point);

CoreBanReason getBanReasonOfPointWithRenjuRangeGroup(CorePoint point, RenjuRangeGroup* rangeGroup);

bool isPointWithRenjuRangeGroupThreeAndThreeBan(CorePoint point, RenjuRangeGroup* rangeGroup);

bool isPointWithRenjuRangeGroupFourAndFourBan(CorePoint point, RenjuRangeGroup* rangeGroup);

bool isPointWithRenjuRangeGroupLongRenjuBan(CorePoint point, RenjuRangeGroup* rangeGroup);

void releaseRenjuRangeGroup(RenjuRangeGroup** rangeGroup);

#endif // RENJU_RANGE_GROUP_H