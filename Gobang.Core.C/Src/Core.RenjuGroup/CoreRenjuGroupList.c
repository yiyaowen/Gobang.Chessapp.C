#include "CoreRenjuGroupList.h"
#include "CoreRenjuPattern.h"
#include "CoreRenjuRangeGroup.h"

#include <stdlib.h>
#include <string.h>

RenjuGroupList* getNewRenjuGroupList(CoreSide favors)
{
    RenjuGroupList* renjuGroupList = (RenjuGroupList*)coreNoNullMalloc(sizeof(RenjuGroupList));
    renjuGroupList->favors = favors;
    renjuGroupList->renjuGroupCount = 4;
    renjuGroupList->renjuGroups = (RenjuGroup**)coreNoNullMalloc(sizeof(RenjuGroup*)*4);
    renjuGroupList->renjuGroups[0] = getNewRowRenjuGroup();
    renjuGroupList->renjuGroups[1] = getNewColumnRenjuGroup();
    renjuGroupList->renjuGroups[2] = getNewBDiagonalRenjuGroup();
    renjuGroupList->renjuGroups[3] = getNewFDiagonalRenjuGroup();
    for (int i = 0; i < CORE_BOARD_SIZE; ++i) {
        for (int j = 0; j < CORE_BOARD_SIZE; ++j) {
            renjuGroupList->gameBoard[i][j] = CORE_SIDE_EMPTY;
            renjuGroupList->banBoard[i][j] = CORE_BAN_REASON_EMPTY;
            renjuGroupList->scoreBoard[i][j] = RENJU_PATTERN_BASE_SCORE;
        }
    }
    return renjuGroupList;
}

void changeRenjuRangeInRenjuGroupListOfPoint(RenjuGroupList* list, CorePoint point, RenjuRangeOperateFunc operateFunc)
{
    operateFunc(
        calculateIndexInStartRenjuInRowRenjuGroupOfPoint(point),
        getRenjuRangeInRowRenjuGroupOfPoint(
            getRowRenjuGroupInRenjuGroupList(list),
            point
        )
    );
    operateFunc(
        calculateIndexInStartRenjuInColumnRenjuGroupOfPoint(point),
        getRenjuRangeInColumnRenjuGroupOfPoint(
            getColumnRenjuGroupInRenjuGroupList(list),
            point
        )
    );
    operateFunc(
        calculateIndexInStartRenjuInBDiagonalRenjuGroupOfPoint(point),
        getRenjuRangeInBDiagonalRenjuGroupOfPoint(
            getBDiagonalRenjuGroupInRenjuGroupList(list),
            point
        )
    );
    operateFunc(
        calculateIndexInStartRenjuInFDiagonalRenjuGroupOfPoint(point),
        getRenjuRangeInFDiagonalRenjuGroupOfPoint(
            getFDiagonalRenjuGroupInRenjuGroupList(list),
            point
        )
    );
}

void addBlackPieceNewPointToRenjuGroupList(CorePoint point, RenjuGroupList* list)
{
    changeRenjuRangeInRenjuGroupListOfPoint(list, point, addNewBlackPieceToRenjuRange);
}

void addWhitePieceNewPointToRenjuGroupList(CorePoint point, RenjuGroupList* list)
{
    changeRenjuRangeInRenjuGroupListOfPoint(list, point, addNewWhitePieceToRenjuRange);
}

void removeBlackPieceOldPointFromRenjuGroupList(CorePoint point, RenjuGroupList* list)
{
    changeRenjuRangeInRenjuGroupListOfPoint(list, point, removeOldBlackPieceFromRenjuRange);
}

void addBlackBanNewPointToRenjuGroupList(CorePoint point, RenjuGroupList* list)
{
    changeRenjuRangeInRenjuGroupListOfPoint(list, point, addNewBlackBanToRenjuRange);
}

void removeBlackBanOldPointFromRenjuGroupList(CorePoint point, RenjuGroupList* list)
{
    changeRenjuRangeInRenjuGroupListOfPoint(list, point, removeOldBlackBanFromRenjuRange);
}

void addNewMoveToRenjuGroupList(CoreSide moveSide, CorePoint movePoint, RenjuGroupList* list)
{
    if (isCoreSideBlack(moveSide)) {
        addBlackPieceNewPointToRenjuGroupList(movePoint, list);
    }
    else {
        addWhitePieceNewPointToRenjuGroupList(movePoint, list);
    }
    list->gameBoard[movePoint.i][movePoint.j] = moveSide;

    list->scoreBoard[movePoint.i][movePoint.j] = RENJU_PATTERN_INVALID_SCORE;
    CorePointList* pointList = getNewRelatedPointListOfPoint(movePoint);
    for (int i = 0; i < pointList->totalPointCount; ++i) {
        if (list->gameBoard[pointList->points[i].i][pointList->points[i].j] != CORE_SIDE_EMPTY)
            continue;
        RenjuRangeGroup* tmpRangeGroup =
            getNewDefaultRenjuRangeGroupInRenjuGroupListOfPoint(list, pointList->points[i]);

        if (!isCoreSideEmpty(list->favors)) {
            list->scoreBoard[pointList->points[i].i][pointList->points[i].j] = RENJU_PATTERN_BASE_SCORE;
            for (int j = 0; j < tmpRangeGroup->renjuRangeCount; ++j) {
                list->scoreBoard[pointList->points[i].i][pointList->points[i].j] +=
                    calculateScoreOfRenjuRangeForSide(tmpRangeGroup->renjuRanges+j, list->favors);
            }
        }

        CoreBanReason banReason = getBanReasonOfPointWithRenjuRangeGroup(pointList->points[i], tmpRangeGroup);
        list->banBoard[pointList->points[i].i][pointList->points[i].j] = banReason;
        if (banReason != CORE_BAN_REASON_EMPTY) {
            addBlackBanNewPointToRenjuGroupList(pointList->points[i], list);
        }
        else {
            removeBlackBanOldPointFromRenjuGroupList(pointList->points[i], list);
        }

        releaseRenjuRangeGroup(&tmpRangeGroup);
    }
    releasePointList(&pointList);
}

CoreSide getWinnerInRenjuGroupList(RenjuGroupList* list)
{
    for (int i = 0; i < list->renjuGroupCount; ++i) {
        RenjuGroup* group = list->renjuGroups[i];
        for (int j = 0; j < group->renjuCount; ++j) {
            Renju* renju = group->renjus[j];
            if (isRenjuPatternFilledWithPieces(renju->blackPattern)) {
                return CORE_SIDE_BLACK;
            }
            else if (isRenjuPatternFilledWithPieces(renju->whitePattern)) {
                return CORE_SIDE_WHITE;
            }
        }
    }
    return CORE_SIDE_EMPTY;
}

bool isBlackTrueFiveRenjuExistsInRenjuGroupList(RenjuGroupList* list)
{
    for (int i = 0; i < list->renjuGroupCount; ++i) {
        RenjuGroup* group = list->renjuGroups[i];
        int fiveRenjuCountPerRenjuRange = 0;
        for (int j = 0; j < group->renjuCount - 1; ++j) {
            Renju* renju = group->renjus[j];
            if (isRenjuPatternFilledWithPieces(renju->blackPattern)) {
                ++fiveRenjuCountPerRenjuRange;
            }
        }
        if (fiveRenjuCountPerRenjuRange == 1) {
            return true;
        }
    }
    return false;
}

CoreBanReason getPoinBanReasonInRenjuGroupList(CorePoint point, RenjuGroupList* list)
{
    addBlackPieceNewPointToRenjuGroupList(point, list);
    if (isBlackTrueFiveRenjuExistsInRenjuGroupList(list))
        return CORE_BAN_REASON_EMPTY;
    removeBlackPieceOldPointFromRenjuGroupList(point, list);
    return list->banBoard[point.i][point.j];
}

TaggedRenjuGroupList* getNewTaggedRenjuGroupList(CoreGameTag tag, CoreSide favors)
{
    TaggedRenjuGroupList* taggedList = (TaggedRenjuGroupList*)coreNoNullMalloc(sizeof(TaggedRenjuGroupList));
    taggedList->tag = tag;
    taggedList->list = getNewRenjuGroupList(favors);
    return taggedList;
}

TaggedRenjuGroupListPool* getNewTaggedRenjuGroupListPool(int maxListCount)
{
    TaggedRenjuGroupListPool* pool = (TaggedRenjuGroupListPool*)coreNoNullMalloc(sizeof(TaggedRenjuGroupListPool));
    pool->maxListCount = maxListCount;
    pool->currentListCount = 0;
    pool->lists = (TaggedRenjuGroupList**)coreNoNullMalloc(sizeof(TaggedRenjuGroupList*)*maxListCount);
    for (int i = 0; i < pool->maxListCount; ++i) {
        pool->lists[i] = NULL;
    }
    return pool;
}

void addNewTaggedRenjuGroupListToTaggedRenjuGroupListPool(CoreGameTag newTag, CoreSide favors, TaggedRenjuGroupListPool* pool)
{
    if (pool->currentListCount >= pool->maxListCount) {
        removeTaggedRenjuGroupListAtIndexInTaggedRenjuGroupListPool(0, pool);
        addNewTaggedRenjuGroupListToTaggedRenjuGroupListPool(newTag, favors, pool);
    }
    for (int i = 0; i < pool->maxListCount; ++i) {
        if (pool->lists[i] == NULL) {
            pool->lists[i] = getNewTaggedRenjuGroupList(newTag, favors);
            ++(pool->currentListCount);
            return;
        }
    }
}

void removeTaggedRenjuGroupListInTaggedRenjuGroupListPool(CoreGameTag tagToRemove, TaggedRenjuGroupListPool* pool)
{
    for (int i = 0; i < pool->maxListCount; ++i) {
        if (pool->lists[i] != NULL && pool->lists[i]->tag == tagToRemove) {
            releaseTaggedRenjuGroupList(&(pool->lists[i]));
            --(pool->currentListCount);
            return;
        }
    }
}

void removeTaggedRenjuGroupListAtIndexInTaggedRenjuGroupListPool(int tagToRemove, TaggedRenjuGroupListPool* pool)
{
    if (pool->currentListCount <= 0) return;
    releaseTaggedRenjuGroupList(&(pool->lists[tagToRemove]));
    --(pool->currentListCount);
}

RenjuGroupList* getRenjuGroupListInTaggedRenjuGroupListPoolWithTag(TaggedRenjuGroupListPool* pool, CoreGameTag tag)
{
    for (int i = 0; i < pool->maxListCount; ++i) {
        if (pool->lists[i] != NULL && pool->lists[i]->tag == tag) {
            return pool->lists[i]->list;
        }
    }
    return NULL;
}

void releaseRenjuGroupList(RenjuGroupList** list)
{
    for (int i = 0; i < (*list)->renjuGroupCount; ++i) {
        releaseRenjuGroup(&(((*list)->renjuGroups)[i]));
    }
    free((*list)->renjuGroups);
    free(*list);
    *list = NULL;
}

void releaseTaggedRenjuGroupList(TaggedRenjuGroupList** taggedList)
{
    releaseRenjuGroupList(&((*taggedList)->list));
    free(*taggedList);
    *taggedList = NULL;
}

void releaseTaggedRenjuGroupListPool(TaggedRenjuGroupListPool** pool)
{
    for (int i = 0; i < (*pool)->maxListCount; ++i) {
        if ((*pool)->lists[i] != NULL) {
            releaseTaggedRenjuGroupList(&((*pool)->lists[i]));
        }
    }
    free((*pool)->lists);
    free(*pool);
    *pool = NULL;
}

#include "CoreBoard.h"

CorePoint getCorePointFromRenjuGroupAlgorithm(RenjuGroupList* list)
{
    CorePoint point = { -1, -1 };
    int tmpMaxScore = 0;
    for (int i = 0; i < CORE_BOARD_SIZE; ++i) {
        for (int j = 0; j < CORE_BOARD_SIZE; ++j) {
            if ((isCoreSideWhite(list->favors) || isBanReasonEmpty(list->banBoard[i][j])) &&
                ((list->scoreBoard[i][j] > tmpMaxScore) ||
                (list->scoreBoard[i][j] == tmpMaxScore &&
                    (absInt(i - CORE_BOARD_SIZE / 2) + absInt(j - CORE_BOARD_SIZE / 2)) <
                    (absInt(point.i - CORE_BOARD_SIZE / 2) + absInt(point.j - CORE_BOARD_SIZE / 2)))))
            {
                point.i = i; point.j = j;
                tmpMaxScore = list->scoreBoard[i][j];
            }
        }
    }
    return point;
}
