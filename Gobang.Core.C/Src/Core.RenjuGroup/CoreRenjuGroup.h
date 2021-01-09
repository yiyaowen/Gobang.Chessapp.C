#ifndef CORE_RENJU_GROUP_H
#define CORE_RENJU_GROUP_H

#include "CoreRenju.h"
#include "CoreDefinitions.h"
#include "CorePair.h"
#include "CoreRenjuRange.h"

#include <stdbool.h>

typedef struct type_RenjuGroup {
    int type;
    char* name;
    int renjuCount;
    Renju** renjus;
} RenjuGroup;

#define RENJU_GROUP_TYPE_ROW        1
#define RENJU_GROUP_TYPE_COLUMN     2
#define RENJU_GROUP_TYPE_BDIAGONAL  3
#define RENJU_GROUP_TYPE_FDIAGONAL  4

RenjuGroup* getNewRenjuGroup();

RenjuGroup* getNewRowRenjuGroup();

RenjuGroup* getNewColumnRenjuGroup();

RenjuGroup* getNewBDiagonalRenjuGroup();

RenjuGroup* getNewFDiagonalRenjuGroup();

int calculateIndexInStartRenjuInRowRenjuGroupOfPoint(CorePoint point);

int calculateIndexInStartRenjuInColumnRenjuGroupOfPoint(CorePoint point);

int calculateIndexInStartRenjuInBDiagonalRenjuGroupOfPoint(CorePoint point);

int calculateIndexInStartRenjuInFDiagonalRenjuGroupOfPoint(CorePoint point);

void allocRenjuGroupNewRenjusWithCount(RenjuGroup* renjuGroup, int count);

IntPair getRenjuIndexRangeInRowRenjuGroupOfPoint(CorePoint point);

IntPair getRenjuIndexRangeInColumnRenjuGroupOfPoint(CorePoint point);

IntPair getRenjuIndexRangeInBDiagonalRenjuGroupOfPoint(CorePoint point);

IntPair getRenjuIndexRangeInFDiagonalRenjuGroupOfPoint(CorePoint point);

RenjuRange getRenjuRangeInRowRenjuGroupOfPoint(RenjuGroup* group, CorePoint point);

RenjuRange getRenjuRangeInColumnRenjuGroupOfPoint(RenjuGroup* group, CorePoint point);

RenjuRange getRenjuRangeInBDiagonalRenjuGroupOfPoint(RenjuGroup* group, CorePoint point);

RenjuRange getRenjuRangeInFDiagonalRenjuGroupOfPoint(RenjuGroup* group, CorePoint point);

bool isRowRenjuIndexRangeValid(int beginIndex, int endIndex);

#define isColumnRenjuIndexRangeValid isRowRenjuIndexRangeValid

bool isBDiagonalRenjuIndexRangeValid(int beginIndex, int endIndex);

#define isFDiagonalRenjuIndexRangeValid isBDiagonalRenjuIndexRangeValid

void releaseRenjuGroup(RenjuGroup** group);

#endif // CORE_RENJU_GROUP_H
