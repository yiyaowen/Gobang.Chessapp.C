#ifndef CORE_DEFINITIONS_H
#define CORE_DEFINITIONS_H

#include "CoreMathUtils.h"

#define CORE_BOARD_SIZE  15

typedef int CoreSide;

#define CORE_SIDE_BLACK -1
#define CORE_SIDE_EMPTY 0
#define CORE_SIDE_WHITE 1

#define isCoreSideBlack(SIDE) ((SIDE) == CORE_SIDE_BLACK)
#define isCoreSideWhite(SIDE) ((SIDE) == CORE_SIDE_WHITE)
#define isCoreSideEmpty(SIDE) ((SIDE) == CORE_SIDE_EMPTY)
#define isCoreSideValid(SIDE) (isCoreSideBlack(SIDE) || isCoreSideWhite(SIDE))

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

typedef CoreSide CoreBoard[CORE_BOARD_SIZE][CORE_BOARD_SIZE];

typedef struct type_CorePrefabConfig {
    CoreSide side;
    CoreLevel level;
} CorePrefabConfig;

#endif // CORE_DEFINITIONS_H
