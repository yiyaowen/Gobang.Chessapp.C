#include "CoreDefinitions.h"
#include "CoreBoard.h"
#include "CoreMathUtils.h"

bool isCoreBoardFull(const CoreBoard board)
{
    for (int i = 0; i < CORE_BOARD_SIZE; ++i) {
        for (int j = 0; j < CORE_BOARD_SIZE; ++j) {
            if (board[i][j] == CORE_SIDE_EMPTY) return false;
        }
    }
    return true;
}

CorePoint getMaxScorePointInCoreScoreBoard(CoreScoreBoard board)
{
    CorePoint point = { -1, -1 };
    int tmpMaxScore = 0;
    for (int i = 0; i < CORE_BOARD_SIZE; ++i) {
        for (int j = 0; j < CORE_BOARD_SIZE; ++j) {
            if ((board[i][j] > tmpMaxScore) ||
                (board[i][j] == tmpMaxScore &&
                (absInt(i - CORE_BOARD_SIZE / 2) + absInt(j - CORE_BOARD_SIZE / 2) <
                (absInt(point.i - CORE_BOARD_SIZE / 2) + absInt(point.j - CORE_BOARD_SIZE / 2)))))
            {
                point.i = i; point.j = j;
                tmpMaxScore = board[i][j];
            }
        }
    }
    return point;
}
