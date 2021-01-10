#include "CoreRenjuGroup.h"
#include "CoreMathUtils.h"

#include <stdlib.h>
#include <string.h>

RenjuGroup* getNewRenjuGroup()
{
    RenjuGroup* renjuGroup = (RenjuGroup*)coreNoNullMalloc(sizeof(RenjuGroup));
    return renjuGroup;
}

RenjuGroup* getNewRowRenjuGroup()
{
    RenjuGroup* rowRenjuGroup = getNewRenjuGroup();
    rowRenjuGroup->type = RENJU_GROUP_TYPE_ROW;
    rowRenjuGroup->name = "Row Renju Group";
    allocRenjuGroupNewRenjusWithCount(rowRenjuGroup, 165);
    return rowRenjuGroup;
}

RenjuGroup* getNewColumnRenjuGroup()
{
    RenjuGroup* columnRenjuGroup = getNewRenjuGroup();
    columnRenjuGroup->type = RENJU_GROUP_TYPE_COLUMN;
    columnRenjuGroup->name = "Column Renju Group";
    allocRenjuGroupNewRenjusWithCount(columnRenjuGroup, 165);
    return columnRenjuGroup;
}

RenjuGroup* getNewBDiagonalRenjuGroup()
{
    RenjuGroup* bDiagonalRenjuGroup = getNewRenjuGroup();
    bDiagonalRenjuGroup->type = RENJU_GROUP_TYPE_BDIAGONAL;
    bDiagonalRenjuGroup->name = "B-Diagonal Renju Group";
    allocRenjuGroupNewRenjusWithCount(bDiagonalRenjuGroup, 121);
    return bDiagonalRenjuGroup;
}

RenjuGroup* getNewFDiagonalRenjuGroup()
{
    RenjuGroup* fDiagonalRenjuGroup = getNewRenjuGroup();
    fDiagonalRenjuGroup->type = RENJU_GROUP_TYPE_FDIAGONAL;
    fDiagonalRenjuGroup->name = "F-Diagonal Renju Group";
    allocRenjuGroupNewRenjusWithCount(fDiagonalRenjuGroup, 121);
    return fDiagonalRenjuGroup;
}

int calculateIndexInStartRenjuInRowRenjuGroupOfPoint(CorePoint point)
{
    return minInt(SINGLE_PATTERN_SEAT_COUNT - 1, point.j);
}

int calculateIndexInStartRenjuInColumnRenjuGroupOfPoint(CorePoint point)
{
    return minInt(SINGLE_PATTERN_SEAT_COUNT - 1, point.i);
}

int calculateIndexInStartRenjuInBDiagonalRenjuGroupOfPoint(CorePoint point)
{
    return minInt(SINGLE_PATTERN_SEAT_COUNT - 1,
        minInt(CORE_BOARD_SIZE - point.i - 1, point.j));
}

int calculateIndexInStartRenjuInFDiagonalRenjuGroupOfPoint(CorePoint point)
{
    return minInt(SINGLE_PATTERN_SEAT_COUNT - 1,
        minInt(CORE_BOARD_SIZE - point.i - 1, CORE_BOARD_SIZE - point.j - 1));
}

void allocRenjuGroupNewRenjusWithCount(RenjuGroup* group, int count)
{
    group->renjuCount = count;
    group->renjus = (Renju**)coreNoNullMalloc(sizeof(Renju*)*count);
    for (int i = 0; i < count; ++i) {
        (group->renjus)[i] = getNewRenju();
    }
}

IntPair getRenjuIndexRangeInRowRenjuGroupOfPoint(CorePoint point)
{
    return makeIntPair(point.i * 11 + maxInt(point.j - 4, 0), point.i * 11 + minInt(point.j, 10));
}

IntPair getRenjuIndexRangeInColumnRenjuGroupOfPoint(CorePoint point)
{
    CorePoint symmetryPoint = { point.j, point.i };
    return getRenjuIndexRangeInRowRenjuGroupOfPoint(symmetryPoint);
}

IntPair getRenjuIndexRangeInBDiagonalRenjuGroupOfPoint(CorePoint point)
{
    static bool isSymmetricPoint = false;
    if (point.i + point.j > 14) {
        CorePoint symmetryPoint = { 14 - point.i, 14 - point.j };
        isSymmetricPoint = true;
        return getRenjuIndexRangeInBDiagonalRenjuGroupOfPoint(symmetryPoint);
    }

    int diagonalOffset = point.i + point.j - 4;
    int startOffset = diagonalOffset * (diagonalOffset + 1) / 2;
    int beginIndex = startOffset + maxInt(point.j - 4, 0);
    int endIndex = startOffset + minInt(point.j, point.i + point.j - 4);
    if (isSymmetricPoint) {
        int tmpIndex = beginIndex;
        beginIndex = 120 - endIndex;
        endIndex = 120 - tmpIndex;
    }

    isSymmetricPoint = false;
    return makeIntPair(beginIndex, endIndex);
}

IntPair getRenjuIndexRangeInFDiagonalRenjuGroupOfPoint(CorePoint point)
{
    CorePoint symmetryPoint = { point.i, 14 - point.j };
    return getRenjuIndexRangeInBDiagonalRenjuGroupOfPoint(symmetryPoint);
}

RenjuRange getRenjuRangeInRowRenjuGroupOfPoint(RenjuGroup* group, CorePoint point)
{
    IntPair indexRange = getRenjuIndexRangeInRowRenjuGroupOfPoint(point);
    int beginIndex = indexRange.first;
    int endIndex = indexRange.second;

    RenjuRange range;
    if (!(range.isValid = isRowRenjuIndexRangeValid(beginIndex, endIndex))) return range;
    range.start = group->renjus + beginIndex;
    range.offset = endIndex - beginIndex;
    return range;
}

RenjuRange getRenjuRangeInColumnRenjuGroupOfPoint(RenjuGroup* group, CorePoint point)
{
    CorePoint symmetryPoint = { point.j, point.i };
    return getRenjuRangeInRowRenjuGroupOfPoint(group, symmetryPoint);
}

RenjuRange getRenjuRangeInBDiagonalRenjuGroupOfPoint(RenjuGroup* group, CorePoint point)
{
    IntPair indexRange = getRenjuIndexRangeInBDiagonalRenjuGroupOfPoint(point);
    int beginIndex = indexRange.first;
    int endIndex = indexRange.second;

    RenjuRange range;
    if (!(range.isValid = isBDiagonalRenjuIndexRangeValid(beginIndex, endIndex))) return range;
    range.start = group->renjus + beginIndex;
    range.offset = endIndex - beginIndex;
    return range;
}

RenjuRange getRenjuRangeInFDiagonalRenjuGroupOfPoint(RenjuGroup* group, CorePoint point)
{
    CorePoint symmetryPoint = { point.i, 14 - point.j };
    return getRenjuRangeInBDiagonalRenjuGroupOfPoint(group, symmetryPoint);
}

bool isRowRenjuIndexRangeValid(int beginIndex, int endIndex)
{
    return beginIndex <= endIndex && beginIndex >= 0 && endIndex < 165;
}

bool isBDiagonalRenjuIndexRangeValid(int beginIndex, int endIndex)
{
    return beginIndex <= endIndex && beginIndex >= 0 && endIndex < 121;
}

void releaseRenjuGroup(RenjuGroup** group)
{
    for (int i = 0; i < (*group)->renjuCount; ++i) {
        releaseRenju(&(((*group)->renjus)[i]));
    }
    free(*group);
    *group = NULL;
}
