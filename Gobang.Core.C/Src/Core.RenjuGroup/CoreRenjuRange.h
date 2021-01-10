#ifndef CORE_RENJU_RANGE_H
#define CORE_RENJU_RANGE_H

#include "CoreRenju.h"
#include "CoreDefinitions.h"

#include <stdbool.h>

typedef struct type_RenjuRange {
    bool isValid;
    Renju** start;
    int offset;
} RenjuRange;

// void func(int indexInStartRenju, RenjuRange range);
typedef void RenjuRangeOperateFunc(int, RenjuRange);

int calculateScoreOfRenjuRangeForSide(const RenjuRange* range, CoreSide side);

RenjuRangeOperateFunc addNewBlackPieceToRenjuRange;

RenjuRangeOperateFunc addNewWhitePieceToRenjuRange;

RenjuRangeOperateFunc removeOldBlackPieceFromRenjuRange;

RenjuRangeOperateFunc addNewBlackBanToRenjuRange;

RenjuRangeOperateFunc removeOldBlackBanFromRenjuRange;

typedef struct type_CorePointList {
    int totalPointCount;
    CorePoint* points;
} CorePointList;

CorePointList* getNewRelatedPointListOfPoint(CorePoint point);

void releasePointList(CorePointList** list);

#endif // CORE_RENJU_RANGE_H