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

CoreBanReason getBanReasonOfPointWithRenjuRangeGroup(CorePoint point, RenjuRangeGroup* rangeGroup)
{
    if (isPointWithRenjuRangeGroupThreeAndThreeBan(point, rangeGroup))
        return CORE_BAN_REASON_THREE_AND_THREE;
    else if (isPointWithRenjuRangeGroupFourAndFourBan(point, rangeGroup))
        return CORE_BAN_REASON_FOUR_AND_FOUR;
    else if (isPointWithRenjuRangeGroupLongRenjuBan(point, rangeGroup))
        return CORE_BAN_REASON_LONG_RENJU;
    return CORE_BAN_REASON_EMPTY;
}

#define calculateIndexInStartRenjuOfPointWithGroupIndex(POINT, INDEX) \
    ((INDEX) == 0 ? calculateIndexInStartRenjuInRowRenjuGroupOfPoint(POINT) : \
    (INDEX) == 1 ? calculateIndexInStartRenjuInColumnRenjuGroupOfPoint(POINT) : \
    (INDEX) == 2 ? calculateIndexInStartRenjuInBDiagonalRenjuGroupOfPoint(POINT) : \
    calculateIndexInStartRenjuInFDiagonalRenjuGroupOfPoint(POINT))

bool isPointWithRenjuRangeGroupThreeAndThreeBan(CorePoint point, RenjuRangeGroup* rangeGroup)
{
    int totalCertainForm = 0;
    for (int i = 0; i < rangeGroup->renjuRangeCount; ++i) {
        if (!rangeGroup->renjuRanges[i].isValid) continue;
        RenjuRange* tmpRange = rangeGroup->renjuRanges + i;
        int indexInStartRenju = calculateIndexInStartRenjuOfPointWithGroupIndex(point, i);
        Renju* tmpLastRenju = *(tmpRange->start + tmpRange->offset);

        if (isRenjuPatternGroupCertainThreeAndThreeForm(indexInStartRenju - tmpRange->offset,
            tmpLastRenju->blackPattern, tmpLastRenju->whitePattern, tmpLastRenju->banPattern))
        {
            ++totalCertainForm;
            if (totalCertainForm >= 2)
                return true;
            continue;
        }

        for (int j = 0; j < tmpRange->offset; ++j) {
            Renju* tmpRenju = *(tmpRange->start + j);
            Renju* tmpNextRenju = *(tmpRange->start + j + 1);
            int indexToMove = indexInStartRenju - j;
            RenjuPattern pureBanPattern =
                copyRenjuPatternRemovePieceAtIndex(tmpRenju->banPattern, indexToMove);
            RenjuPattern nextPureBanPattern =
                copyRenjuPatternRemovePieceAtIndex(tmpNextRenju->banPattern, indexToMove - 1);

            if (isRenjuPatternGroupCertainThreeAndThreeForm(indexToMove,
                tmpRenju->blackPattern, tmpRenju->whitePattern, pureBanPattern) ||
                (isRenjuPatternGroupLatentThreeAndThreeForm(indexToMove,
                tmpRenju->blackPattern, tmpRenju->whitePattern, pureBanPattern) &&
                isRenjuPatternGroupLatentThreeAndThreeForm(indexToMove - 1,
                tmpNextRenju->blackPattern, tmpNextRenju->whitePattern, nextPureBanPattern)))
            {
                ++totalCertainForm;
                if (totalCertainForm >= 2) {
                    return true;
                }
                else {
                    break;
                }
            }
        }
    }
    return false;
}

bool isPointWithRenjuRangeGroupFourAndFourBan(CorePoint point, RenjuRangeGroup* rangeGroup)
{
    int totalCertainForm = 0;
    for (int i = 0; i < rangeGroup->renjuRangeCount; ++i) {
        if (!rangeGroup->renjuRanges[i].isValid) continue;
        RenjuRange* tmpRange = rangeGroup->renjuRanges + i;
        int indexInStartRenju = calculateIndexInStartRenjuOfPointWithGroupIndex(point, i);

        for (int j = 0; j < tmpRange->offset; ++j) {
            Renju* tmpRenju = *(tmpRange->start + j);
            int indexToMove = indexInStartRenju - j;
            RenjuPattern pureBanPattern =
                copyRenjuPatternRemovePieceAtIndex(tmpRenju->banPattern, indexToMove);

            if (j < tmpRange->offset - 1) {
                Renju* tmpJumpRenju = *(tmpRange->start + j + 2);
                RenjuPattern jumpPureBanPattern =
                    copyRenjuPatternRemovePieceAtIndex(tmpJumpRenju->banPattern, indexToMove - 2);
                if (isRenjuPatternGroupParallelFourAndFourForm(indexToMove,
                    tmpRenju->blackPattern, tmpRenju->whitePattern, pureBanPattern) &&
                    isRenjuPatternGroupParallelFourAndFourForm(indexToMove - 2,
                    tmpJumpRenju->blackPattern, tmpJumpRenju->whitePattern, jumpPureBanPattern))
                {
                    return true;
                }
            }

            if (isRenjuPatternGroupCertainFourAndFourForm(indexToMove,
                tmpRenju->blackPattern, tmpRenju->whitePattern, pureBanPattern))
            {
                ++totalCertainForm;
                if (totalCertainForm >= 2) {
                    return true;
                }
                else {
                    break;
                }
            }
        }
    }
    return false;
}

bool isPointWithRenjuRangeGroupLongRenjuBan(CorePoint point, RenjuRangeGroup* rangeGroup)
{
    for (int i = 0; i < rangeGroup->renjuRangeCount; ++i) {
        if (!rangeGroup->renjuRanges[i].isValid) continue;
        RenjuRange* tmpRange = rangeGroup->renjuRanges + i;
        int indexInStartRenju = calculateIndexInStartRenjuOfPointWithGroupIndex(point, i);

        for (int j = 0; j < tmpRange->offset; ++j) {
            Renju* tmpRenju = *(tmpRange->start + j);
            Renju* tmpNextRenju = *(tmpRange->start + j + 1);
            int indexToMove = indexInStartRenju - j;
            RenjuPattern pureBanPattern =
                copyRenjuPatternRemovePieceAtIndex(tmpRenju->banPattern, indexToMove);
            RenjuPattern nextPureBanPattern =
                copyRenjuPatternRemovePieceAtIndex(tmpNextRenju->banPattern, indexToMove - 1);

            if (isRenjuPatternGroupLatentLongRenjuForm(tmpRenju->blackPattern,
                tmpRenju->whitePattern, pureBanPattern) &&
                isRenjuPatternGroupLatentLongRenjuForm(tmpNextRenju->blackPattern,
                tmpNextRenju->whitePattern, nextPureBanPattern))
            {
                return true;
            }
        }
    }
    return false;
}

void releaseRenjuRangeGroup(RenjuRangeGroup** rangeGroup)
{
    free((*rangeGroup)->renjuRanges);
    free(*rangeGroup);
    *rangeGroup = NULL;
}