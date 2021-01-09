#include "CoreRenjuRangeGroup.h"

#include <stdlib.h>

RenjuRangeGroup* getNewDefaultRenjuRangeGroupInRenjuGroupListOfPoint(RenjuGroupList* list, CorePoint point)
{
    RenjuRangeGroup* rangeGroup = (RenjuRangeGroup*)malloc(sizeof(RenjuRangeGroup));
    rangeGroup->renjuRangeCount = 4;
    rangeGroup->renjuRanges = (RenjuRange*)malloc(sizeof(RenjuRange)*4);
    rangeGroup->renjuRanges[0] = getRenjuRangeInRowRenjuGroupOfPoint(getRowRenjuGroupInRenjuGroupList(list), point);
    rangeGroup->renjuRanges[1] = getRenjuRangeInColumnRenjuGroupOfPoint(getColumnRenjuGroupInRenjuGroupList(list), point);
    rangeGroup->renjuRanges[2] = getRenjuRangeInBDiagonalRenjuGroupOfPoint(getBDiagonalRenjuGroupInRenjuGroupList(list), point);
    rangeGroup->renjuRanges[3] = getRenjuRangeInFDiagonalRenjuGroupOfPoint(getFDiagonalRenjuGroupInRenjuGroupList(list), point);
    return rangeGroup;
}

void releaseRenjuRangeGroup(RenjuRangeGroup** rangeGroup)
{
    free((*rangeGroup)->renjuRanges);
    free(*rangeGroup);
    *rangeGroup = NULL;
}