#include "CoreRandom.h"
#include "CoreRandomUtility.h"

#include <stdlib.h>

CorePoint getCorePointFromRandomAlgorithm(const CoreBoard board)
{
    CorePoint point = { -1, -1 };

    CorePoint* validPoints = malloc(sizeof(CorePoint)*CORE_BOARD_SIZE*CORE_BOARD_SIZE);
    int validPointsCount = filterValidPointsFromCoreBoard(board, validPoints);

    if (validPointsCount == 0) return point;

    point = validPoints[getRandomIntFromLeftInclusiveRange(0, validPointsCount)];

    free(validPoints);
    return point;
}
