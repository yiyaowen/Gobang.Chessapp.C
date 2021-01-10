#ifndef RENJU_GROUP_LIST_H
#define RENJU_GROUP_LIST_H

#include "CoreRenjuGroup.h"

typedef struct type_RenjuGroupList {
    CoreSide favors;
    int renjuGroupCount;
    RenjuGroup** renjuGroups;
    CoreBoard gameBoard;
    CoreBanBoard banBoard;
    CoreScoreBoard scoreBoard;
} RenjuGroupList;

RenjuGroupList* getNewRenjuGroupList(CoreSide favors);

#define getRowRenjuGroupInRenjuGroupList(LIST)          ((LIST)->renjuGroups[0])
#define getColumnRenjuGroupInRenjuGroupList(LIST)       ((LIST)->renjuGroups[1])
#define getBDiagonalRenjuGroupInRenjuGroupList(LIST)    ((LIST)->renjuGroups[2])
#define getFDiagonalRenjuGroupInRenjuGroupList(LIST)    ((LIST)->renjuGroups[3])

void changeRenjuRangeInRenjuGroupListOfPoint(RenjuGroupList* list, CorePoint point, RenjuRangeOperateFunc operateFunc);

void addBlackPieceNewPointToRenjuGroupList(CorePoint point, RenjuGroupList* list);

void addWhitePieceNewPointToRenjuGroupList(CorePoint point, RenjuGroupList* list);

void addBlackBanNewPointToRenjuGroupList(CorePoint point, RenjuGroupList* list);

void removeBlackBanOldPointFromRenjuGroupList(CorePoint point, RenjuGroupList* list);

void addNewMoveToRenjuGroupList(CoreSide moveSide, CorePoint movePoint, RenjuGroupList* list);

CoreSide getWinnerInRenjuGroupList(RenjuGroupList* list);

bool isBlackTrueFiveRenjuExistsInRenjuGroupList(RenjuGroupList* list);

CoreBanReason getPoinBanReasonInRenjuGroupList(CorePoint point, RenjuGroupList* list);

typedef struct type_TaggedRenjuGroupList {
    CoreGameTag tag;
    RenjuGroupList* list;
} TaggedRenjuGroupList;

TaggedRenjuGroupList* getNewTaggedRenjuGroupList(CoreGameTag tag, CoreSide favors);

typedef struct type_TaggedRenjuGroupListPool {
    int maxListCount;
    int currentListCount;
    TaggedRenjuGroupList** lists;
} TaggedRenjuGroupListPool;

#define GENERAL_TAGGED_RENJU_GROUP_LIST_POOL_CAPACITY   3

TaggedRenjuGroupListPool* getNewTaggedRenjuGroupListPool(int maxListCount);

void addNewTaggedRenjuGroupListToTaggedRenjuGroupListPool(CoreGameTag newTag, CoreSide favors, TaggedRenjuGroupListPool* pool);

void removeTaggedRenjuGroupListInTaggedRenjuGroupListPool(CoreGameTag tagToRemove, TaggedRenjuGroupListPool* pool);

void removeTaggedRenjuGroupListAtIndexInTaggedRenjuGroupListPool(int indexToRemove, TaggedRenjuGroupListPool* pool);

RenjuGroupList* getRenjuGroupListInTaggedRenjuGroupListPoolWithTag(TaggedRenjuGroupListPool* pool, CoreGameTag tag);

void releaseRenjuGroupList(RenjuGroupList** list);

void releaseTaggedRenjuGroupList(TaggedRenjuGroupList** taggedList);

void releaseTaggedRenjuGroupListPool(TaggedRenjuGroupListPool** pool);

CorePoint getCorePointFromRenjuGroupAlgorithm(RenjuGroupList* list);

#endif // RENJU_GROUP_LIST_H
