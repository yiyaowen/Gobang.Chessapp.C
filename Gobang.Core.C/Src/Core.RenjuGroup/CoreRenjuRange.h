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

int calculateScoreOfRenjuRangeForSide(const RenjuRange* range, CoreSide side);

void addNewBlackPieceToRenjuRange(int indexInStartRenju, RenjuRange range);

void addNewWhitePieceToRenjuRange(int indexInStartRenju, RenjuRange range);

void addNewPieceToRenjuRange(CoreSide whichSide, int indexInStartRenju, RenjuRange range);

typedef struct type_CorePointList {
    int totalPointCount;
    CorePoint* points;
} CorePointList;

CorePointList* getNewRelatedPointListOfPoint(CorePoint point);

void releasePointList(CorePointList** list);

#endif // CORE_RENJU_RANGE_H