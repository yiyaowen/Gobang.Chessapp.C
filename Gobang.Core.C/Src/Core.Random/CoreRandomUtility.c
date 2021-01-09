#include <stdlib.h>
#include <time.h>

#include "CoreRandomUtility.h"
#include "CoreDefinitions.h"

int filterValidPointsFromCoreBoard(const CoreBoard board, CorePoint* validPoints)
{
    int validPointsCount = 0;
    for (int i = 0; i < CORE_BOARD_SIZE; ++i) {
        for (int j = 0; j < CORE_BOARD_SIZE; ++j) {
            if (board[i][j] == CORE_SIDE_EMPTY) {
                CorePoint point = { i, j };
                validPoints[validPointsCount++] = point;
            }
        }
    }
    return validPointsCount;
}

int getRandomIntFromLeftInclusiveRange(int left, int right)
{
    srand((unsigned)time(0));
    return rand() % (right-left) + left;
}
