#include "Core.h"
#include "CoreDefinitions.h"
#include "CoreBoard.h"
#include "CoreRandom.h"
#include "CoreRenjuGroupList.h"
#include "CoreRandomUtility.h"
#include "CorePointField.h"

#include <stdlib.h>

TaggedRenjuGroupListPool* pool = NULL;

void initializeGobangCore()
{
    pool = getNewTaggedRenjuGroupListPool(GENERAL_TAGGED_RENJU_GROUP_LIST_POOL_CAPACITY);
}

void releaseGobangCore()
{
    releaseTaggedRenjuGroupListPool(&pool);
}

void createNewCoreGameWithTag(CoreGameTag tag, CoreSide favors)
{
    addNewTaggedRenjuGroupListToTaggedRenjuGroupListPool(tag, favors, pool);
}

void addNewMovePieceToCoreGameWithTag(CoreSide side, CorePoint point, CoreGameTag tag)
{
    if (isCoreSideValid(side) && isCorePointValid(point)) {
        RenjuGroupList* list = getRenjuGroupListInTaggedRenjuGroupListPoolWithTag(pool, tag);
        if (list == NULL) {
            addNewTaggedRenjuGroupListToTaggedRenjuGroupListPool(tag, side, pool);
            list = getRenjuGroupListInTaggedRenjuGroupListPoolWithTag(pool, tag);
        }
        addNewMoveToRenjuGroupList(side, point, list);
    }
}

void removeCoreGameWithTag(CoreGameTag tag)
{
    removeTaggedRenjuGroupListInTaggedRenjuGroupListPool(tag, pool);
}

#define getCoreLevelFromValidRandomInteger(VALID_INT) \
    ((VALID_INT) == 0 ? CORE_LEVEL_DRUNK : \
    (VALID_INT) == 1 ? CORE_LEVEL_LOW : \
    (VALID_INT) == 2 ? CORE_LEVEL_MIDDLE : \
    CORE_LEVEL_HIGH)

CorePoint getCorePointFromCoreAlgorithm(CorePrefabConfig* config, CoreGameTag tag)
{
    CorePoint point = { -1, -1 };
    CoreLevel gameLevel = config->level;
    RenjuGroupList* list = getRenjuGroupListInTaggedRenjuGroupListPoolWithTag(pool, tag);
    if (list == NULL || isCoreBoardFull(list->gameBoard)) return point;
choose_game_level:
    switch (gameLevel)
    {
        case CORE_LEVEL_DRUNK:
        {
            return getCorePointFromRandomAlgorithm(list->gameBoard);
        }
        case CORE_LEVEL_LOW:
        {
            point = getCorePointFromPointFieldAlgorithm(list);
            return point;
        }
        case CORE_LEVEL_MIDDLE:
        {
            point = getCorePointFromRenjuGroupAlgorithm(list);
            return point;
        }
        case CORE_LEVEL_HIGH:
        {
            point = getCorePointFromRenjuGroupAlgorithm(list);
            return point;
        }
        case CORE_LEVEL_RANDOM:
        {
            gameLevel = getCoreLevelFromValidRandomInteger(
                getRandomIntFromLeftInclusiveRange(0, 4));
            goto choose_game_level;
        }
        default:
        {
            return point;
        }
    }
}

CoreSide getWinnerSideInCoreGameWithTag(CoreGameTag tag)
{
    RenjuGroupList* list = getRenjuGroupListInTaggedRenjuGroupListPoolWithTag(pool, tag);
    return getWinnerInRenjuGroupList(list);
}

CoreBanReason getPointBanReasonInCoreGameWithTag(CorePoint point, CoreGameTag tag)
{
    RenjuGroupList* list = getRenjuGroupListInTaggedRenjuGroupListPoolWithTag(pool, tag);
    return getPoinBanReasonInRenjuGroupList(point, list);
}