#ifndef CORE_DEFINITIONS_H
#define CORE_DEFINITIONS_H

#include "CoreMathUtils.h"
#include <stdlib.h>

#define CORE_BOARD_SIZE  15

typedef int CoreSide;

#define CORE_SIDE_BLACK -1
#define CORE_SIDE_EMPTY 0
#define CORE_SIDE_WHITE 1

#define isCoreSideBlack(SIDE) ((SIDE) == CORE_SIDE_BLACK)
#define isCoreSideWhite(SIDE) ((SIDE) == CORE_SIDE_WHITE)
#define isCoreSideEmpty(SIDE) ((SIDE) == CORE_SIDE_EMPTY)
#define isCoreSideValid(SIDE) (isCoreSideBlack(SIDE) || isCoreSideWhite(SIDE))

typedef int CoreBanReason;

#define CORE_BAN_REASON_EMPTY   0
#define CORE_BAN_REASON_THREE_AND_THREE 1
#define CORE_BAN_REASON_FOUR_AND_FOUR   2
#define CORE_BAN_REASON_LONG_RENJU      3

#define isBanReasonEmpty(REASON) ((REASON) == CORE_BAN_REASON_EMPTY)
#define isBanReasonThreeAndThree(REASON) ((REASON) == CORE_BAN_REASON_THREE_AND_THREE)
#define isBanReasonFourAndFour(REASON) ((REASON) == CORE_BAN_REASON_FOUR_AND_FOUR)
#define isBanReasonLongRenju(REASON) ((REASON) == CORE_BAN_REASON_LONG_RENJU)

typedef int CoreLevel;

#define CORE_LEVEL_DRUNK    -100
#define CORE_LEVEL_LOW      0
#define CORE_LEVEL_MIDDLE   1
#define CORE_LEVEL_HIGH     2
#define CORE_LEVEL_RANDOM   100

typedef int CoreGameTag;

typedef struct type_CorePoint {
    int i;
    int j;
} CorePoint;

#define isCorePointValid(POINT) \
    (0 <= minInt((POINT).i, (POINT).j) && maxInt((POINT).i, (POINT).j) < CORE_BOARD_SIZE)

typedef int CoreScoreBoard[CORE_BOARD_SIZE][CORE_BOARD_SIZE];

typedef CoreBanReason CoreBanBoard[CORE_BOARD_SIZE][CORE_BOARD_SIZE];

typedef CoreSide CoreBoard[CORE_BOARD_SIZE][CORE_BOARD_SIZE];

typedef struct type_CorePrefabConfig {
    CoreSide side;
    CoreLevel level;
} CorePrefabConfig;

void* coreNoNullMalloc(size_t blockSize);

#endif // CORE_DEFINITIONS_H
