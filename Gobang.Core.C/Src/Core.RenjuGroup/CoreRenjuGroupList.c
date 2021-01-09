#include "CoreRenjuGroupList.h"
#include "CoreRenjuPattern.h"
#include "CoreRenjuRangeGroup.h"

#include <stdlib.h>
#include <string.h>

RenjuGroupList* getNewRenjuGroupList(CoreSide favors)
{
    RenjuGroupList* renjuGroupList = (RenjuGroupList*)malloc(sizeof(RenjuGroupList));
    renjuGroupList->favors = favors;
    renjuGroupList->renjuGroupCount = 4;
    renjuGroupList->renjuGroups = (RenjuGroup**)malloc(sizeof(RenjuGroup*)*4);
    renjuGroupList->renjuGroups[0] = getNewRowRenjuGroup();
    renjuGroupList->renjuGroups[1] = getNewColumnRenjuGroup();
    renjuGroupList->renjuGroups[2] = getNewBDiagonalRenjuGroup();
    renjuGroupList->renjuGroups[3] = getNewFDiagonalRenjuGroup();
    for (int i = 0; i < CORE_BOARD_SIZE; ++i) {
        for (int j = 0; j < CORE_BOARD_SIZE; ++j) {
            renjuGroupList->gameBoard[i][j] = CORE_SIDE_EMPTY;
            renjuGroupList->scoreBoard[i][j] = RENJU_PATTERN_BASE_SCORE;
        }
    }
    return renjuGroupList;
}

void addBlackPieceNewPointToRenjuGroupList(CorePoint point, RenjuGroupList* list)
{
    addNewPieceToRenjuRange(
        CORE_SIDE_BLACK,
        calculateIndexInStartRenjuInRowRenjuGroupOfPoint(point),
        getRenjuRangeInRowRenjuGroupOfPoint(
            getRowRenjuGroupInRenjuGroupList(list),
            point
        )
    );
    addNewPieceToRenjuRange(
        CORE_SIDE_BLACK,
        calculateIndexInStartRenjuInColumnRenjuGroupOfPoint(point),
        getRenjuRangeInColumnRenjuGroupOfPoint(
            getColumnRenjuGroupInRenjuGroupList(list),
            point
        )
    );
    addNewPieceToRenjuRange(
        CORE_SIDE_BLACK,
        calculateIndexInStartRenjuInBDiagonalRenjuGroupOfPoint(point),
        getRenjuRangeInBDiagonalRenjuGroupOfPoint(
            getBDiagonalRenjuGroupInRenjuGroupList(list),
            point
        )
    );
    addNewPieceToRenjuRange(
        CORE_SIDE_BLACK,
        calculateIndexInStartRenjuInFDiagonalRenjuGroupOfPoint(point),
        getRenjuRangeInFDiagonalRenjuGroupOfPoint(
            getFDiagonalRenjuGroupInRenjuGroupList(list),
            point
        )
    );
}

void addWhitePieceNewPointToRenjuGroupList(CorePoint point, RenjuGroupList* list)
{
    addNewPieceToRenjuRange(
        CORE_SIDE_WHITE,
        calculateIndexInStartRenjuInRowRenjuGroupOfPoint(point),
        getRenjuRangeInRowRenjuGroupOfPoint(
            getRowRenjuGroupInRenjuGroupList(list),
            point
        )
    );
    addNewPieceToRenjuRange(
        CORE_SIDE_WHITE,
        calculateIndexInStartRenjuInColumnRenjuGroupOfPoint(point),
        getRenjuRangeInColumnRenjuGroupOfPoint(
            getColumnRenjuGroupInRenjuGroupList(list),
            point
        )
    );
    addNewPieceToRenjuRange(
        CORE_SIDE_WHITE,
        calculateIndexInStartRenjuInBDiagonalRenjuGroupOfPoint(point),
        getRenjuRangeInBDiagonalRenjuGroupOfPoint(
            getBDiagonalRenjuGroupInRenjuGroupList(list),
            point
        )
    );
    addNewPieceToRenjuRange(
        CORE_SIDE_WHITE,
        calculateIndexInStartRenjuInFDiagonalRenjuGroupOfPoint(point),
        getRenjuRangeInFDiagonalRenjuGroupOfPoint(
            getFDiagonalRenjuGroupInRenjuGroupList(list),
            point
        )
    );
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

    if (isCoreSideEmpty(list->favors)) return;

    list->scoreBoard[movePoint.i][movePoint.j] = RENJU_PATTERN_INVALID_SCORE;
    CorePointList* pointList = getNewRelatedPointListOfPoint(movePoint);
    for (int i = 0; i < pointList->totalPointCount; ++i) {
        if (list->gameBoard[pointList->points[i].i][pointList->points[i].j] != CORE_SIDE_EMPTY)
            continue;
        list->scoreBoard[pointList->points[i].i][pointList->points[i].j] = RENJU_PATTERN_BASE_SCORE;
        RenjuRangeGroup* tmpRangeGroup =
            getNewDefaultRenjuRangeGroupInRenjuGroupListOfPoint(list, pointList->points[i]);
        for (int j = 0; j < tmpRangeGroup->renjuRangeCount; ++j) {
            list->scoreBoard[pointList->points[i].i][pointList->points[i].j] +=
                calculateScoreOfRenjuRangeForSide(tmpRangeGroup->renjuRanges+j, list->favors);
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

TaggedRenjuGroupList* getNewTaggedRenjuGroupList(CoreGameTag tag, CoreSide favors)
{
    TaggedRenjuGroupList* taggedList = (TaggedRenjuGroupList*)malloc(sizeof(TaggedRenjuGroupList));
    taggedList->tag = tag;
    taggedList->list = getNewRenjuGroupList(favors);
    return taggedList;
}
TaggedRenjuGroupListPool* getNewTaggedRenjuGroupListPool(int maxListCount)
{
    TaggedRenjuGroupListPool* pool = (TaggedRenjuGroupListPool*)malloc(sizeof(TaggedRenjuGroupListPool));
    pool->maxListCount = maxListCount;
    pool->currentListCount = 0;
    pool->lists = (TaggedRenjuGroupList**)malloc(sizeof(TaggedRenjuGroupList*)*maxListCount);
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
    return getMaxScorePointInCoreScoreBoard(list->scoreBoard);
}
