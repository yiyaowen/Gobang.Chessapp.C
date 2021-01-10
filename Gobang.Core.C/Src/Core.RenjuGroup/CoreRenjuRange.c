#include "CoreRenjuRange.h"

#include <stdlib.h>

int calculateScoreOfRenjuRangeForSide(const RenjuRange* range, CoreSide side)
{
    if (!range->isValid) return 0;
    int totalScore = 0;
    for (int i = 0; i <= range->offset; ++i) {
        int tmpBlackPieceCount =
            getTotalPieceCountOfRenjuPattern((*(range->start+i))->blackPattern);
        int tmpWhitePieceCount =
            getTotalPieceCountOfRenjuPattern((*(range->start+i))->whitePattern);
        if (tmpBlackPieceCount != 0 && tmpWhitePieceCount != 0) {
            totalScore += RENJU_PATTERN_MIXED_SCORE;
        }
        else if (tmpBlackPieceCount != 0) {
            if (isCoreSideBlack(side)) {
                totalScore += getFavorsScoreOfPieceCount(tmpBlackPieceCount);
            }
            else {
                totalScore += getAdverseScoreOfPieceCount(tmpBlackPieceCount);
            }
        }
        else if (tmpWhitePieceCount != 0) {
            if (isCoreSideBlack(side)) {
                totalScore += getAdverseScoreOfPieceCount(tmpWhitePieceCount);
            }
            else {
                totalScore += getFavorsScoreOfPieceCount(tmpWhitePieceCount);
            }
        }
        else {
            totalScore += RENJU_PATTERN_EMPTY_SCORE;
        }
    }
    return totalScore;
}

void addNewBlackPieceToRenjuRange(int indexInStartRenju, RenjuRange range)
{
    if (!range.isValid) return;
    for (int i = 0; i <= range.offset; ++i) {
        Renju* tmpRenju = *(range.start + i);
        addNewPieceToRenjuPatternAtIndex(
            (*(range.start + i))->blackPattern,
            indexInStartRenju - i
        );
        tmpRenju = *(range.start + i);
    }
}

void addNewWhitePieceToRenjuRange(int indexInStartRenju, RenjuRange range)
{
    if (!range.isValid) return;
    for (int i = 0; i <= range.offset; ++i) {
        addNewPieceToRenjuPatternAtIndex(
            (*(range.start + i))->whitePattern,
            indexInStartRenju - i
        );
    }
}

void removeOldBlackPieceFromRenjuRange(int indexInStartRenju, RenjuRange range)
{
    if (!range.isValid) return;
    for (int i = 0; i <= range.offset; ++i) {
        removeOldPieceFromRenjuPatternAtIndex(
            (*(range.start + i))->blackPattern,
            indexInStartRenju - i
        );
    }
}

void addNewBlackBanToRenjuRange(int indexInStartRenju, RenjuRange range)
{
    if (!range.isValid) return;
    for (int i = 0; i <= range.offset; ++i) {
        addNewBanToRenjuPatternAtIndex(
            (*(range.start + i))->banPattern,
            indexInStartRenju - i
        );
    }
}

void removeOldBlackBanFromRenjuRange(int indexInStartRenju, RenjuRange range)
{
    if (!range.isValid) return;
    for (int i = 0; i <= range.offset; ++i) {
        removeOldBanFromRenjuPatternAtIndex(
            (*(range.start + i))->banPattern,
            indexInStartRenju - i
        );
    }
}

CorePointList* getNewRelatedPointListOfPoint(CorePoint point)
{
    CorePointList* list = (CorePointList*)coreNoNullMalloc(sizeof(CorePointList));
    int topLimitCount = minInt(4, point.i),
        bottomLimitCount = minInt(4, CORE_BOARD_SIZE - point.i - 1),
        leftLimitCount = minInt(4, point.j),
        rightLimitCount = minInt(4, CORE_BOARD_SIZE - point.j - 1);
    int topLeftLimitCount = minInt(topLimitCount, leftLimitCount),
        topRightLimitCount = minInt(topLimitCount, rightLimitCount),
        bottomLeftLimitCount = minInt(bottomLimitCount, leftLimitCount),
        bottomRightLimitCount = minInt(bottomLimitCount, rightLimitCount);
    list->totalPointCount = topLimitCount + bottomLimitCount + leftLimitCount + rightLimitCount +
        + topLeftLimitCount + topRightLimitCount + bottomLeftLimitCount + bottomRightLimitCount;
    list->points = (CorePoint*)coreNoNullMalloc(sizeof(CorePoint)*list->totalPointCount);
    int offsetInList = 0;
    for (int i = 0; i < topLimitCount; ++i) {
        list->points[offsetInList + i].i = point.i - i - 1;
        list->points[offsetInList + i].j = point.j;
    }
    offsetInList += topLimitCount;
    for (int i = 0; i < bottomLimitCount; ++i) {
        list->points[offsetInList + i].i = point.i + i + 1;
        list->points[offsetInList + i].j = point.j;
    }
    offsetInList += bottomLimitCount;
    for (int i = 0; i < leftLimitCount; ++i) {
        list->points[offsetInList + i].i = point.i;
        list->points[offsetInList + i].j = point.j - i - 1;
    }
    offsetInList += leftLimitCount;
    for (int i = 0; i < rightLimitCount; ++i) {
        list->points[offsetInList + i].i = point.i;
        list->points[offsetInList + i].j = point.j + i + 1;
    }
    offsetInList += rightLimitCount;
    for (int i = 0; i < topLeftLimitCount; ++i) {
        list->points[offsetInList + i].i = point.i - i - 1;
        list->points[offsetInList + i].j = point.j - i - 1;
    }
    offsetInList += topLeftLimitCount;
    for (int i = 0; i < topRightLimitCount; ++i) {
        list->points[offsetInList + i].i = point.i - i - 1;
        list->points[offsetInList + i].j = point.j + i + 1;
    }
    offsetInList += topRightLimitCount;
    for (int i = 0; i < bottomLeftLimitCount; ++i) {
        list->points[offsetInList + i].i = point.i + i + 1;
        list->points[offsetInList + i].j = point.j - i - 1;
    }
    offsetInList += bottomLeftLimitCount;
    for (int i = 0; i < bottomRightLimitCount; ++i) {
        list->points[offsetInList + i].i = point.i + i + 1;
        list->points[offsetInList + i].j = point.j + i + 1;
    }
    return list;
}

void releasePointList(CorePointList** list)
{
    free((*list)->points);
    free(*list);
    *list = NULL;
}
